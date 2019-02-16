/*
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "threadpool.h"
#include "SpeechPersistent.h"
#include "dprintf.h"

#define MAX_INDEX 64
#define MAX_SPEECH_BUFFER_LEN 16*1024
#define MAX_NLP_BUFFER_LEN 128*1024


#define PERSISITENT_BUFFER_SIZE MAX_INDEX*MAX_SPEECH_BUFFER_LEN //16k
typedef struct __Speech{
    char *id;
    int type;
    char *buf;
    int len;
    int completed;
}PersistentHandle_t;

static threadpool_t *gThreadPool = NULL;
static void*gInitParam = NULL;
static char*gPreName =NULL;

//max  200K * 20 * 4 = 16000K
//normal 50K * 20 * 4 = 40000K
#define MAX_PERSISTENT_COUNT 20 

//maybe need a lock
static int gPersistentCount = 0;
#define SN_LENGTH 33
static char gSDId[SN_LENGTH] = {0};
char * getDeviceId(){
    return gSDId;
}
#define MAX_PATH_INDEX 4
#define DEFAULT_PATH0 "/data/speech0"
#define DEFAULT_PATH1 "/data/speech1"
#define DEFAULT_PATH2 "/data/speech2"
#define DEFAULT_PATH3 "/data/speech3"

static char *gDefaultLocal[MAX_PATH_INDEX]={
    DEFAULT_PATH0,
    DEFAULT_PATH1,
    DEFAULT_PATH2,
    DEFAULT_PATH3
};
static char *gpDefaultPath = NULL;
static int gnDefaultPathIndex = 0;



#define DEFAULT_MODE 0777

int rmDir(char *dir)  { 
    int ret = 0;
    DIR *dp;  
    struct dirent *entry;  
    struct stat statbuf; 
    if(dir == NULL){
        DprintfE("bad dir path: %s\n", dir);  
        return -1;      
    }
    ret = lstat(dir, &statbuf);
    if(ret != 0){
        DprintfE("lstat %s failed: error:%d(%s)\n",dir, errno, strerror(errno)); 
        return -1;  
    }
    if(S_ISDIR(statbuf.st_mode)){
        if ((dp = opendir(dir)) == NULL)  {  
            DprintfE("cannot open directory: %s\n", dir);  
            return -1;  
        }  
        chdir (dir);  
        while ((entry = readdir(dp)) != NULL)  {  
            lstat(entry->d_name, &statbuf);  
            if (S_ISREG(statbuf.st_mode))  {  
                remove(entry->d_name);  
            }  
        }  
    }else{
        remove(dir);
    }
    return 0;  
}

#define DOT_OR_DOTDOT(s) ((s)[0] == '.' && (!(s)[1] || ((s)[1] == '.' && !(s)[2])))
static char* xasprintf(const char *format, ...)
{
	va_list p;
	int r;
	char *string_ptr;

	va_start(p, format);
	r = vasprintf(&string_ptr, format, p);
	va_end(p);
	return string_ptr;
}

static char* last_char_is(const char *s, int c)
{
	if (s && *s) {
		size_t sz = strlen(s) - 1;
		s += sz;
		if ( (unsigned char)*s == c)
			return (char*)s;
	}
	return NULL;
}

static char* concat_path_file(const char *path, const char *filename)
{
	char *lc;

	if (!path)
		path = "";
	lc = last_char_is(path, '/');
	while (*filename == '/')
		filename++;
	return xasprintf("%s%s%s", path, (lc==NULL ? "/" : ""), filename);
}

char* concat_subpath_file(const char *path, const char *f)
{
	if (f && DOT_OR_DOTDOT(f))
		return NULL;
	return concat_path_file(path, f);
}

int remove_file(const char *path)
{
	struct stat path_stat;

	if (lstat(path, &path_stat) < 0) {
		if (errno != ENOENT) {
			DprintfE("can't stat '%s'\n", path);
			return -1;
		}
		return 0;
	}

	if (S_ISDIR(path_stat.st_mode)) {
		DIR *dp;
		struct dirent *d;
		int status = 0;

		dp = opendir(path);
		if (dp == NULL) {
			return -1;
		}

		while ((d = readdir(dp)) != NULL) {
			char *new_path;
			new_path = concat_subpath_file(path, d->d_name);
			if (new_path == NULL)
				continue;
			if (remove_file(new_path) < 0)
				status = -1;
			free(new_path);
		}

		if (closedir(dp) < 0) {
			DprintfE("can't close '%s'\n", path);
			return -1;
		}

		if (rmdir(path) < 0) {
			DprintfE("can't remove '%s'\n", path);
			return -1;
		} else {
            DprintfI("remove '%s'\n", path);
        }
		return status;
	}

	if (unlink(path) < 0) {
		DprintfE("can't remove '%s'\n", path);
		return -1;
	} else{
        DprintfI("remove '%s'\n", path);
    }
	return 0;
}


static void * UploadTask(void *param)
{
    int ret = 0;
    char* path = (char*)param; 
    if(path == NULL){
        DprintfE("bad path for upload\n");
        return NULL;
    }
    gnDefaultPathIndex = (gnDefaultPathIndex+1)%MAX_PATH_INDEX;
    gpDefaultPath = gDefaultLocal[gnDefaultPathIndex];
    free(gPreName);
    gPreName = NULL;

    remove_file(path);
	
    return NULL;
}

void checkUpload()
{
    int ret = 0;
    pthread_t pthreadid;
    pthread_create(&pthreadid, NULL, UploadTask, (void *)gpDefaultPath);
    DprintfI("checkUpload gPersistentCount %d %s\n", gPersistentCount, gpDefaultPath);
    pthread_detach(pthreadid);
}
static int doCheckAndTriggerUpload(){
    if(gPersistentCount == MAX_PERSISTENT_COUNT-1){
        checkUpload();    
    }
    gPersistentCount = (gPersistentCount+1)%MAX_PERSISTENT_COUNT;
    return 0;
}


static void initPath()
{
    int ret = 0;
    char path[256] = {0};
    ret = access(gpDefaultPath,DEFAULT_MODE);
    if(ret != 0){
        ret = mkdir(gpDefaultPath, DEFAULT_MODE);
        if(ret < 0 && EEXIST != errno){
            DprintfE("mkdir %s failed: error:%d(%s)\n",gpDefaultPath, errno, strerror(errno));
            return;
        }
    }
     
    sprintf(path,"%s/%s",gpDefaultPath,"flying-pig");
    ret = access(path,DEFAULT_MODE);
    if(ret != 0){
        ret = mkdir(path, DEFAULT_MODE);
        if(ret < 0 && errno != EEXIST){
            DprintfE("mkdir %s failed: error:%d(%s)\n",path, errno, strerror(errno));
            return;
        }
    }
    sprintf(path,"%s/%s/%s",gpDefaultPath,"flying-pig", getDeviceId());
    ret = access(path,DEFAULT_MODE);
    if(ret != 0){
        ret = mkdir(path, DEFAULT_MODE);
        if(ret < 0 && errno != EEXIST){
            DprintfE("mkdir %s failed: error:%d(%s)\n",path, errno, strerror(errno));
            return;
        }
    }
    gPreName = strdup(path);
    DprintfI("initPath %s\n",gPreName);
}


static char* getIDbytime()
{
    time_t t = time(NULL);
    struct tm* timeNow = localtime((const time_t *)(&t));
    char buffer[20] = {0};
    sprintf(buffer,"%04d%02d%02d%02d%02d%02d",
        timeNow->tm_year+1900,timeNow->tm_mon,timeNow->tm_mday,
        timeNow->tm_hour,timeNow->tm_min,timeNow->tm_sec);
    buffer[strlen(buffer)] = '\0';
    return strdup(buffer);
}
static char * getDirByID(char* id)
{
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s",gPreName, id);
    buffer[strlen(buffer)] = '\0';
    return strdup(buffer);   
}
static char * getNameByID(char* id)
{
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s/%s",gPreName, id, "input.pcm");
    buffer[strlen(buffer)] = '\0';
    return strdup(buffer);   
}
static char * getASRByID(char* id)
{
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s/%s",gPreName, id, "outputasr.json");
    buffer[strlen(buffer)] = '\0';
    return strdup(buffer);     
}
static char * getNLPByID(char* id)
{
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s/%s",gPreName, id, "output.json");
    buffer[strlen(buffer)] = '\0';
    return strdup(buffer);     
}

static void * StartTask(void *param)
{
    int ret = 0;
    
    PersistentHandle_t* handle = (PersistentHandle_t*)param; 
    if(handle == NULL){
        DprintfE("no mem\n");
        return NULL;
    }
    if(handle->type != TYPE_START){
        DprintfE("bad type\n");
        free(handle);
        return NULL;
    }
    DprintfD("%s id:%s handle:%p in\n",__FUNCTION__, handle->id, handle);
    gpDefaultPath = gDefaultLocal[gnDefaultPathIndex];
    initPath();
    
    char *name = getDirByID(handle->id);
    ret = mkdir(name, DEFAULT_MODE);
    if(ret < 0 && errno != EEXIST){
        DprintfE("mkdir %s failed: error:%d(%s)\n",name,errno,strerror(errno));
        if(name)free(name);
        free(handle);
        return NULL;
    }
    DprintfD("StartTask create work space %s\n",name);
    DprintfD("%s id:%s handle:%p done\n",__FUNCTION__, handle->id, handle);

    if(name)free(name);
    free(handle);
    return NULL;
}
static void * StopTask(void *param)
{
    int ret = 0;
    char* dir = NULL;
    PersistentHandle_t* handle = (PersistentHandle_t*)param; 
    if(handle == NULL){
        DprintfE("bad parameter\n");
        return NULL;
    }
    if(handle->type != TYPE_STOP){
        DprintfE("bad type\n");
    }
    DprintfD("%s id:%s handle:%p in\n",__FUNCTION__, handle->id, handle);
    if(!handle->completed){
        dir = getDirByID(handle->id);
        remove_file(dir);
        free(dir);
    }else{
        doCheckAndTriggerUpload();
    }
    DprintfI("%s id:%p handle:%p completed:%d\n",__FUNCTION__, handle->id, handle, handle->completed);
    DprintfD("%s id:%s handle:%p done\n",__FUNCTION__, handle->id, handle);

    if(handle->buf){
        free(handle->buf);
    }
    free(handle->id);
    free(handle);
    return NULL;
}
static void * ProcessTask(void *param)
{
    int ret = 0;
    int filefd = 0;
    char* id = NULL;
    char *name = NULL;
    
    PersistentHandle_t* handle = (PersistentHandle_t*)param; 
    if(handle == NULL){
        DprintfE("bad parameter\n");
        return NULL;
    }
    DprintfD("%s id:%s handle:%p in\n",__FUNCTION__, handle->id, handle);
    switch(handle->type){
        case TYPE_ASR:{
            name = getASRByID(handle->id);
        }
        break;
        case TYPE_NLP:{
            name = getNLPByID(handle->id);
        }
        break;
        case TYPE_SEEPCH:{
            name = getNameByID(handle->id);
        }
        break;
        default:
            DprintfE("bad type %d\n",handle->type);
            if(handle->buf)free(handle->buf);
            free(handle);
            return NULL;
    }
    filefd = open(name,O_RDWR|O_APPEND|O_CREAT,DEFAULT_MODE);
    if(filefd <= 0){
        DprintfE("create %s failed: error:%d(%s)\n",name,errno,strerror(errno));
        if(name)free(name);
        if(handle->buf)free(handle->buf);
        free(handle);
        return NULL;
    }
    ret = write(filefd, handle->buf, handle->len);
    if(ret != handle->len){
        DprintfE("write %s fd %d failed: ret:%d error:%d(%s)\n", name, filefd, ret, errno, strerror(errno));
        close(filefd);
        if(handle->buf)free(handle->buf);
        free(handle);
        return NULL;
    }else{
        DprintfD("%s type %d write %s %d Bytes\n", __FUNCTION__, handle->type, name, ret);
    }
    DprintfD("%s id:%s handle:%p done\n",__FUNCTION__, handle->id, handle);

    if(name)free(name);
    close(filefd);
    if(handle->buf)free(handle->buf);
    free(handle);
    return NULL;
}

void Init(const void*param)
{ 
    DprintfD("%s in\n",__FUNCTION__);
    gPersistentCount = 0;
    gnDefaultPathIndex  = 0;
    
    if(param == NULL){
        memcpy(gSDId,"UBTUBT0123456789UBTUBT0123456789",strlen("UBTUBT0123456789UBTUBT0123456789"));
    }else{
        memcpy(gSDId,(char*)param,strlen((char*)param));
    }
    gInitParam = (void*)param;

    gThreadPool = threadpool_create(1, 1, MAX_INDEX);
    if(gThreadPool == NULL){
        DprintfE("create threadpool failed\n");
        return;
    }
    DprintfI("%s done: param=%s,Pool=%p\n", __FUNCTION__, gSDId, gThreadPool);
    DprintfD("%s out\n",__FUNCTION__);
}
void* speechStart()
{
    int ret = 0;
    
    if(gThreadPool == NULL){
        DprintfE("ThreadPool no inited\n");
        return NULL;
    }
    DprintfD("%s in\n",__FUNCTION__);
    
    PersistentHandle_t* phandle = (PersistentHandle_t*)malloc(sizeof(PersistentHandle_t)); 
    if(phandle == NULL){
        DprintfE("no mem\n");
        return NULL;
    }
    memset(phandle, 0, sizeof(PersistentHandle_t));
    char *speechID = getIDbytime();
    phandle->id = speechID;
    phandle->type = TYPE_START;
    phandle->completed = 1;
    
    DprintfD("%s type=%d, id=%s\n",__FUNCTION__,phandle->type,phandle->id);
    ret = threadpool_add_task(gThreadPool, StartTask, phandle);
    if(ret != 0){
        DprintfE("poll full\n");
        free(phandle);
        return NULL;
    }
    DprintfD("%s id=%P done\n",__FUNCTION__,speechID);//don't use phandle->id here
    return speechID;
}

int speechProcess(void* handle,const char *buf, int len, PersistentType_t type)
{
    int ret = 0;
    char * temp = NULL;
    if(handle == NULL || buf == NULL || len <= 0 
         || len > MAX_NLP_BUFFER_LEN || gThreadPool == NULL){
        DprintfE("bad parameter\n");
        return -1;
    }  
    DprintfD("%s type %d id=%s in\n",__FUNCTION__,type,(char*)handle);
        
    PersistentHandle_t* handlelocal = (PersistentHandle_t*)malloc(sizeof(PersistentHandle_t)); 
    if(handlelocal == NULL){
        printf("no mem\n");
        return -1;
    }  
    handlelocal->id = (char*)handle;
    
    char *nlpHeader = "{\"source\":\"dingdang3.0\",\"result\":[";
    int lenHeader = strlen(nlpHeader);
    char *nlpTail = "]}";
    int lenTail = strlen(nlpTail);
    DprintfD("lenHeader=%d, lenTail=%d\n", lenHeader, lenTail);
    
    if(type == TYPE_NLP){
        handlelocal->buf = (char*)malloc(len+lenHeader+lenTail);
    }else{
        handlelocal->buf = (char*)malloc(len);
    }
    if(handlelocal->buf == NULL){
        free(handlelocal);
        DprintfE("no mem,buff alloc failed\n");
        return -1;
    }
    
    if(type == TYPE_NLP){
        memcpy(handlelocal->buf,nlpHeader, lenHeader);
        memcpy((char*)(handlelocal->buf+lenHeader), buf, len);
        memcpy((char*)(handlelocal->buf+lenHeader+len), nlpTail, lenTail);
        handlelocal->len = lenHeader + len + lenTail;
    }else{
        memcpy(handlelocal->buf, buf, len);
        handlelocal->len = len;
    }
    handlelocal->type = type;
    handlelocal->completed = 1;
    
    DprintfD("%s type=%d, id=%s\n", __FUNCTION__, handlelocal->type, handlelocal->id);
    ret = threadpool_add_task(gThreadPool, ProcessTask, handlelocal);
    if(ret != 0){
        DprintfE("poll full\n");
        free(handlelocal);
        return -1;
    }
    DprintfD("%s id=%p done\n", __FUNCTION__, (char*)handle);
    return 0;
}

int speechStop(void* handle, int isCompleted)
{
    int ret = 0;
    if(handle == NULL || gThreadPool == NULL){
        DprintfE("bad parameter\n");
        return -1;
    }
    DprintfD("%s id=%s in\n",__FUNCTION__,(char*)handle);
    
    PersistentHandle_t* handlelocal = (PersistentHandle_t*)malloc(sizeof(PersistentHandle_t)); 
    if(handlelocal == NULL){
        DprintfE("no mem\n");
        return -1;
    }  
    memset(handlelocal, 0 ,sizeof(PersistentHandle_t));
    handlelocal->type = TYPE_STOP;
    handlelocal->id = (char*)handle;
    handlelocal->completed = isCompleted;
    DprintfD("%s type=%d, id=%s\n",__FUNCTION__,handlelocal->type,handlelocal->id);
    ret = threadpool_add_task(gThreadPool, StopTask, handlelocal);
    if(ret != 0){
        DprintfE("poll full\n");
        free(handlelocal);
        return -1;
    }
    DprintfD("%s id=%p done\n",__FUNCTION__,(char*)handle);
    return 0;
}

void unInit()
{
    DprintfI("%s done: param=%s,Pool=%p\n", __FUNCTION__, gSDId, gThreadPool);
    gInitParam = NULL;
    //if(gThreadPool)threadpool_free(gThreadPool);
    if(gThreadPool)threadpool_destroy(gThreadPool);
    if(gPreName)free(gPreName);
}



