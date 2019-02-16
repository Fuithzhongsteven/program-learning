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
#include "SpeechPersistent.h"



#define INPUT_FILE "/dev/urandom"
static void speechProcessInterrupt(int inputFd,char *buffer){
    int ret = 0;
    int i = 0;
    void *handle = speechStart();
    do{
        ret = read(inputFd,buffer,1024);
        buffer[1024] = '\0';
        if(ret > 0){
            speechProcess(handle, buffer, ret, TYPE_SEEPCH);
        }
    }while(i--);
    //printf("%s speechStop in\n",__FUNCTION__);
    speechStop(handle,0); 
    //printf("%s speechStop out\n",__FUNCTION__);
}


static void speechProcessSuccess(int inputFd,char *buffer){
    int ret = 0;
    int i = 0;
    void *handle = speechStart();
    i = 32;
    do{
        ret = read(inputFd,buffer,1024);
        buffer[1024] = '\0';
        if(ret > 0){
            speechProcess(handle, buffer, ret, TYPE_SEEPCH);
        }
    }while(i--);
    ret = read(inputFd,buffer,2048);
    buffer[2048] = '\0';
    if(ret > 0){
        speechProcess(handle, buffer, ret, TYPE_ASR);
    }    
    ret = read(inputFd,buffer,4096);
    buffer[4096] = '\0';
    if(ret > 0){
        speechProcess(handle, buffer, ret, TYPE_NLP);
    }
    usleep(100*1000);
    //printf("%s speechStop in\n",__FUNCTION__);
    speechStop(handle,1);
    //printf("%s speechStop out\n",__FUNCTION__);
}


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
    speechProcessInterrupt(fd,buff);
    usleep(100*1000);
    for(i=0;i<64;i++){
        speechProcessSuccess(fd,buff);
        usleep(300*1000);
    }
    unInit();
    close(fd);
}



