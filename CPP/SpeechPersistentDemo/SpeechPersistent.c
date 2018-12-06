/*
 */
#include "UBTSpeechPersistent.h"
#include "threadpool.h"
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


#define Dprintf(x...) printf(x)



#define MAX_INDEX 64
#define MAX_SPEECH_BUFFER_LEN 1024
#define MAX_NLP_BUFFER_LEN 8*1024


#define PERSISITENT_BUFFER_SIZE MAX_INDEX*MAX_SPEECH_BUFFER_LEN //16k
typedef struct __Speech{
    char *id;
    int type;
    char *buf;
    int len;
    int completed;
}PersistentHandle_t;

static threadpool_t *gThreadPool = NULL;
//static int state = STATE_IDLE;
static void*gInitParam = NULL;
static char*gPreName =NULL;

#define MAX_PERSISTENT_COUNT 100
static int gPersistentCount = 0;//完整保存的次数

char * getDeviceId(){
    return "UBTSteven0123456";
}

#define DEFAULT_MODE 0777

int rmDir(char *dir)  { 
    int ret = 0;
    DIR *dp;  
    struct dirent *entry;  
    struct stat statbuf; 
    if(dir == NULL){
        Dprintf("bad dir path: %s\n", dir);  
        return -1;      
    }
    ret = lstat(dir, &statbuf);
    if(ret != 0){
        Dprintf("lstat %s failed: error:%d(%s)\n",dir, errno, strerror(errno)); 
        return -1;  
    }
    if(S_ISDIR(statbuf.st_mode)){
        if ((dp = opendir(dir)) == NULL)  {  
            Dprintf("cannot open directory: %s\n", dir);  
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


#define DEFAULT_PATH "/data/golden-pig"
static void initPath(){
    int ret = 0;
    char path[128] = {0};
    ret = access(DEFAULT_PATH,DEFAULT_MODE);
    if(ret != 0){
        ret = mkdir(DEFAULT_PATH, DEFAULT_MODE);
        if(ret < 0 && EEXIST != errno){
            Dprintf("mkdir %s failed: error:%d(%s)\n",DEFAULT_PATH, errno, strerror(errno));
            return;
        }
    }
    sprintf(path,"%s/%s",DEFAULT_PATH,getDeviceId());
    ret = access(path,DEFAULT_MODE);
    if(ret != 0){
        ret = mkdir(path, DEFAULT_MODE);
        if(ret < 0 && errno != EEXIST){
            Dprintf("mkdir %s failed: error:%d(%s)\n",path, errno, strerror(errno));
            return;
        }
    }
    gPreName = strdup(path);
}


static char* getIDbytime(){
    time_t t = time(NULL);
    struct tm* timeNow = localtime((const time_t *)(&t));
    char buffer[256] = {0};
    sprintf(buffer,"%04d%02d%02d%02d%02d%02d",
        timeNow->tm_year+1900,timeNow->tm_mon,timeNow->tm_mday,
        timeNow->tm_hour,timeNow->tm_min,timeNow->tm_sec);
    //Dprintf("ID:%s\n",buffer);
    return strdup(buffer);
}
static char * getDirByID(char* id){
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s",gPreName, id);
    return strdup(buffer);   
}
static char * getNameByID(char* id){
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s/%s",gPreName, id, "input.pcm");
    return strdup(buffer);   
}
static char * getASRByID(char* id){
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s/%s",gPreName, id, "outputasr.json");
    return strdup(buffer);     
}
static char * getNLPByID(char* id){
    char buffer[256] = {0};
    sprintf(buffer,"%s/%s/%s",gPreName, id, "output.json");
    return strdup(buffer);     
}

static void * StartTask(void *param){
    int ret = 0;
    //Dprintf("%s in\n",__FUNCTION__);
    PersistentHandle_t* handle = (PersistentHandle_t*)param; 
    if(handle == NULL){
        Dprintf("no mem\n");
        return NULL;
    }
    if(handle->type != TYPE_START){
        Dprintf("bad type\n");
        free(handle);
        return NULL;
    }
    char* id = (char *)(handle->id);
    char *name = getDirByID(id);
    ret = mkdir(name, DEFAULT_MODE);
    if(ret < 0 && errno != EEXIST){
        Dprintf("mkdir %s failed: error:%d(%s)\n",name,errno,strerror(errno));
        if(name)free(name);
        free(handle);
        return NULL;
    }
    if(name)free(name);
    free(handle);
    //Dprintf("%s done\n",__FUNCTION__);
    return NULL;
}
static void * StopTask(void *param){
    int ret = 0;
    char* dir = NULL;
    PersistentHandle_t* handle = (PersistentHandle_t*)param; 
    //Dprintf("%s in:%p\n",__FUNCTION__,handle);
    if(handle == NULL){
        Dprintf("bad parameter\n");
        return NULL;
    }
    if(handle->type != TYPE_STOP){
        Dprintf("bad type\n");
    }
    if(!handle->completed){
        dir = getDirByID(handle->id);
        rmDir(dir);
        free(dir);
    }
    if(handle->buf){
        free(handle->buf);
    }
    free(handle->id);
    free(handle);
    //Dprintf("%s done\n",__FUNCTION__);
    return NULL;
}
static void * ProcessTask(void *param){
    int ret = 0;
    int filefd = 0;
    char* id = NULL;
    char *name = NULL;
    
    PersistentHandle_t* handle = (PersistentHandle_t*)param; 
    //Dprintf("%s in:%p\n",__FUNCTION__,handle);
    if(handle == NULL){
        Dprintf("bad parameter\n");
        return NULL;
    }
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
            Dprintf("bad type %d\n",handle->type);
            if(handle->buf)free(handle->buf);
            free(handle);
            return NULL;
    }
    filefd = open(name,O_RDWR|O_APPEND|O_CREAT,DEFAULT_MODE);
    if(filefd <= 0){
        Dprintf("create %s failed: error:%d(%s)\n",name,errno,strerror(errno));
        if(name)free(name);
        if(handle->buf)free(handle->buf);
        free(handle);
        return NULL;
    }
    ret = write(filefd, handle->buf, handle->len);
    if(ret != handle->len){
        Dprintf("write %s fd %d failed: ret:%d error:%d(%s)\n", name, filefd, ret, errno, strerror(errno));
        close(filefd);
        if(handle->buf)free(handle->buf);
        free(handle);
        return NULL;
    }else{
        Dprintf("write %s %d Bytes\n",name,ret);
    }
    if(name)free(name);
    close(filefd);
    if(handle->buf)free(handle->buf);
    free(handle);
    //Dprintf("%s done\n",__FUNCTION__);
    return NULL;
}


int calDirSize(const      char* path, unsigned long* size) {
    FTS *fts;
    FTSENT *p;
    unsigned long matchedSize = 0;
    char *argv[] = { (char*) path.c_str(), nullptr };
    if (!(fts = fts_open(argv, FTS_PHYSICAL | FTS_NOCHDIR | FTS_XDEV, NULL))) {
        if (errno != ENOENT) {
            PLOG(ERROR) << "Failed to fts_open " << path;
        }
        return -1;
    }
    while ((p = fts_read(fts)) != NULL) {
        switch (p->fts_info) {
        case FTS_D:
        case FTS_DEFAULT:
        case FTS_F:
        case FTS_SL:
        case FTS_SLNONE:
            matchedSize += (p->fts_statp->st_blocks * 512);
            break;
        }
    }
    fts_close(fts);
    *size += matchedSize;
    return 0;
}


static void * TimerTask(void *param){
    //todo check space ,trigger upload to server and clean    
}


void Init(void*param){   
    gThreadPool = threadpool_create(1, 1, MAX_INDEX);
    if(gThreadPool == NULL){
        Dprintf("create threadpool failed\n");
        return;
    }
    gInitParam = param;
    initPath();
}
void* speechStart(){
    int ret = 0;
    //Dprintf("%s in\n",__FUNCTION__);
    
    if(gThreadPool == NULL){
        Dprintf("get id failed\n");
        return NULL;
    }
    PersistentHandle_t* phandle = (PersistentHandle_t*)malloc(sizeof(PersistentHandle_t)); 
    if(phandle == NULL){
        Dprintf("no mem\n");
        return NULL;
    }
    memset(phandle, 0 ,sizeof(PersistentHandle_t));
    phandle->id = getIDbytime();
    phandle->type = TYPE_START;
    phandle->completed = 1;
    
    //Dprintf("%s type=%d, id=%s\n",__FUNCTION__,phandle->type,phandle->id);
    ret = threadpool_add_task(gThreadPool, StartTask, phandle);
    if(ret != 0){
        Dprintf("poll full\n");
        free(phandle);
        return NULL;
    }
    //Dprintf("%s done,handle=%p\n",__FUNCTION__,phandle);
    return phandle->id;
}

int speechProcess(void* handle,char *buf, int len, PersistentType_t type){
    int ret = 0;
    char * temp = NULL;
    //Dprintf("%s in\n",__FUNCTION__);
    if(handle == NULL | buf == NULL | len <= 0 
        | len > MAX_NLP_BUFFER_LEN | gThreadPool == NULL){
        Dprintf("bad parameter\n");
        return -1;
    }

    PersistentHandle_t* handlelocal = (PersistentHandle_t*)malloc(sizeof(PersistentHandle_t)); 
    if(handlelocal == NULL){
        Dprintf("no mem\n");
        return -1;
    }  
    handlelocal->id = (char*)handle;
    handlelocal->buf = (char*)malloc(len); 
    if(handlelocal->buf == NULL){
        free(handlelocal);
        Dprintf("no mem,buff alloc failed\n");
        return -1;
    }
    memcpy(handlelocal->buf, buf, len);
    handlelocal->len = len;
    handlelocal->type = type;
    handlelocal->completed = 1;
    
    //Dprintf("%s type=%d, id=%s\n",__FUNCTION__,handlelocal->type,handlelocal->id);
    ret = threadpool_add_task(gThreadPool, ProcessTask, handlelocal);
    if(ret != 0){
        Dprintf("poll full\n");
        free(handlelocal);
        return -1;
    }
    //Dprintf("%s done,handle=%p\n",__FUNCTION__,handlelocal);
    return 0;
}

int speechStop(void* handle, int isCompleted){
    int ret = 0;
    //Dprintf("%s in\n",__FUNCTION__);
    if(handle == NULL | gThreadPool == NULL){
        Dprintf("bad parameter\n");
        return -1;
    }
    PersistentHandle_t* handlelocal = (PersistentHandle_t*)malloc(sizeof(PersistentHandle_t)); 
    if(handlelocal == NULL){
        Dprintf("no mem\n");
        return -1;
    }  
    memset(handlelocal, 0 ,sizeof(PersistentHandle_t));
    handlelocal->type = TYPE_STOP;
    handlelocal->id = (char*)handle;
    handlelocal->completed = isCompleted;
    Dprintf("%s type=%d, id=%s\n",__FUNCTION__,handlelocal->type,handlelocal->id);
    ret = threadpool_add_task(gThreadPool, StopTask, handlelocal);
    if(ret != 0){
        Dprintf("poll full\n");
        free(handlelocal);
        return -1;
    }
    //Dprintf("%s done,handle=%p\n",__FUNCTION__,handlelocal);
    return 0;
}

void unInit(){
    gInitParam = NULL;
    //if(gThreadPool)threadpool_free(gThreadPool);
    if(gThreadPool)threadpool_destroy(gThreadPool);
    if(gPreName)free(gPreName);
}



