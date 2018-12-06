/*
 */
#include "threadpool.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#include "threadpool.h"
#include "UBTSpeechPersistent.h"



#define INPUT_FILE "/dev/urandom"


int main(int argc, char *argv[]) {
    int ret = 0;
    int i = 16;
    char buff[4098] = {0};
    printf("speech demo");
    int fd = open(INPUT_FILE,O_RDONLY);
    if(fd <= 0){
        printf("open %s failed: error:%d(%s)\n",INPUT_FILE, errno, strerror(errno));
        return 0;
    }
    Init(NULL);
    void *handle = speechStart();
    do{
        ret = read(fd,buff,1024);
        if(ret > 0){
            speechProcess(handle, buff, ret, TYPE_SEEPCH);
        }
    }while(i--);
    speechStop(handle,0); 
    handle = NULL;
    handle = speechStart();
    i = 32;
    do{
        ret = read(fd,buff,1024);
        if(ret > 0){
            speechProcess(handle, buff, ret, TYPE_SEEPCH);
        }
    }while(i--);
    ret = read(fd,buff,2048);
    if(ret > 0){
        speechProcess(handle, buff, ret, TYPE_ASR);
    }    
    ret = read(fd,buff,4096);
    if(ret > 0){
        speechProcess(handle, buff, ret, TYPE_NLP);
    }
    usleep(100*1000);
    speechStop(handle,1);
}



