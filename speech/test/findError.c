#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#define N_BYTES 4
#define FRAM_SIZE 12

int fileBuffer[FRAM_SIZE];
int main(int argc, char *argv[])
{
    FILE *file;
    int ret =0;
    bool firstReadFlag = false;
    int readCount = 0;
    int sucCount = 0;
    int errCount = 0;
    
    if(argc != 2){
        printf("please intput audio file \n");
        exit(1);
    }
    
    file = fopen(argv[1], "r+b");
    
    if(NULL == file){
        printf("fopen %s error!\n", argv[1]);
        exit(1);
    }
    while(1){
        ret = fread(fileBuffer, N_BYTES, 1, file);
        if(ret <= 0 ){
            printf("file is over\n");
            break;
        }
        if(0x100 == ((*fileBuffer) & 0xF00)){
            ret = fread(fileBuffer+1, N_BYTES, FRAM_SIZE-1, file);
            if(ret <= 0 ){
                printf("file 7 7 7 7 7 7 7 is over\n");
                break;
            }
            
            if(   (0x200 == ((*(fileBuffer+1)) & 0xF00))
                &&(0x300 == ((*(fileBuffer+2)) & 0xF00))
                &&(0x400 == ((*(fileBuffer+3)) & 0xF00))
                &&(0x500 == ((*(fileBuffer+4)) & 0xF00))
                &&(0x600 == ((*(fileBuffer+5)) & 0xF00))
                &&(0x700 == ((*(fileBuffer+6)) & 0xF00))
                &&(0x800 == ((*(fileBuffer+7)) & 0xF00))
                &&(0x900 == ((*(fileBuffer+8)) & 0xF00))
                &&(0xA00 == ((*(fileBuffer+9)) & 0xF00))
                &&(0xB00 == ((*(fileBuffer+10)) & 0xF00))
                &&(0xC00 == ((*(fileBuffer+11)) & 0xF00))
            )
            {
                sucCount += FRAM_SIZE*N_BYTES;
            }else{
                printf("0x200 error readCount = 0x%8x,sucCount=%d, errCount=%d\n", readCount, sucCount, errCount);
                errCount += FRAM_SIZE*N_BYTES;
            }
            readCount += FRAM_SIZE*N_BYTES;
            
        }else{
            printf("0x100 error readCount = 0x%x\n", readCount);
            readCount += 1*N_BYTES;
            errCount += N_BYTES;
        }
    }
    return 0;
}
