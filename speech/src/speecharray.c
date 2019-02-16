/*
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <tinyalsa/asoundlib.h>

#include "dprintf.h"
#include "speecharray.h"

#define HW_BUFFER_COUNT 2
#define HW_OUT_DATA_RATIO 4
#define SINGLE_SAMPLE_BYTES 48

#define DEFAULT_SAMOLE_RATE     96000
#define DEFAULT_PERIOD_SIZE     3072    // 32bits 12channels 32ms
#define DEFAULT_PERIOD_COUNT    2
#define DEFAULT_CHANNEL_COUNT   2
#define DEFAULT_PCM_FLAGS       PCM_IN

#define MAX_READ_COUNT DEFAULT_PERIOD_SIZE*DEFAULT_PERIOD_COUNT*DEFAULT_CHANNEL_COUNT*4/HW_OUT_DATA_RATIO

#define LOCAL_UNUSED(expr) do { (void)(expr); } while (0)


//hw config
struct pcm_config hw_config = {
    .channels = DEFAULT_CHANNEL_COUNT,
    .rate = DEFAULT_SAMOLE_RATE,
    .period_size = DEFAULT_PERIOD_SIZE,
    .period_count = DEFAULT_PERIOD_COUNT,
    .format = PCM_FORMAT_S32_LE,
    .start_threshold = 0,
    .stop_threshold = 0,
    .silence_threshold = 0,
    .silence_size =0,
};

struct SpeechArrayHandle_t{
	SpeechArray_t array_config;
    int out_align;
    
	//runtime private
	struct pcm *pcm_handle;
    struct pcm_config hwconfig;
    pthread_mutex_t lock;
	pthread_cond_t buff_wait;
    
    int buff_size;
    char *buffer;
    int data_size;

    int hw_align;
    int ratio;
};
#define DEBUG_DUMP_DATA 1
#if DEBUG_DUMP_DATA
#define DUMP_DATA_FILE "/sdcard/org-data.pcm"
int dumpfd = 0;
#endif
static int parseData_INT32(char *data, int len);
static int skipData(char *data, int len);

int speechArrayInit(){
    #if DEBUG_DUMP_DATA
    dumpfd = open(DUMP_DATA_FILE,O_CREAT|O_RDWR,0777);
    if(dumpfd < 0){
        DprintfE("open %s failed,error:%d(%s)\n",DUMP_DATA_FILE,dumpfd,strerror(errno));
    }
    #endif
	return 0;
}
SpeechArrayHandle_t *speechArrayOpen(SpeechArray_t *config){
	if(config == NULL){
		DprintfE("%s failed: bad parameters config=null\n",__FUNCTION__);
		return NULL;
	}
	SpeechArrayHandle_t* handle = malloc(sizeof(SpeechArrayHandle_t));
	if(handle == NULL){
		DprintfE("%s failed: no memory\n",__FUNCTION__);
		return NULL;
	}
	memset(handle,0,sizeof(SpeechArrayHandle_t));
    
    if(pthread_mutex_init(&(handle->lock), NULL) !=0){
        DprintfE("%s failed: pthread_mutex_init failed\n",__FUNCTION__);
        free(handle);
        return NULL;
    }
    if(pthread_cond_init(&(handle->buff_wait), NULL) !=0){
        DprintfE("%s failed: pthread_cond_init failed\n",__FUNCTION__);
        pthread_mutex_destroy(&(handle->lock));
        free(handle);
        return NULL;
    }
    
    pthread_mutex_lock(&(handle->lock));
	memcpy(&(handle->array_config),config, sizeof(SpeechArray_t));
    handle->out_align = pcm_format_to_bits(handle->array_config.format) * handle->array_config.channels/8;
    
    memcpy(&(handle->hwconfig),&hw_config, sizeof(struct pcm_config));

    handle->pcm_handle = pcm_open(
        config->card, config->device, DEFAULT_PCM_FLAGS, &(handle->hwconfig)
    );
    if (!handle->pcm_handle){
        DprintfE("Unable to open PCM device\n");
        goto Error;
    } 
    if(!pcm_is_ready(handle->pcm_handle)) {
        DprintfE("device is not ready:error(%s)\n",pcm_get_error(handle->pcm_handle));
        goto Error;
    }
    handle->buff_size =HW_BUFFER_COUNT * pcm_frames_to_bytes(handle->pcm_handle, pcm_get_buffer_size(handle->pcm_handle));
    handle->hw_align = handle->hwconfig.channels *  pcm_format_to_bits(handle->hwconfig.format)/8;
    handle->ratio = HW_OUT_DATA_RATIO;
    //handle->buff_size += handle->out_align*handle->ratio;
    handle->buffer = (char*)malloc(handle->buff_size);
    if(handle->buffer == NULL){
        DprintfE("no mem, malloc buffer failed\n");
        goto Error;
    }
    handle->data_size = 0;
    DprintfD("%s: success, rate:%d, buff_size:%d\n", __FUNCTION__, config->rate, handle->buff_size);
    pthread_mutex_unlock(&(handle->lock));
    
    return handle;
    
Error:
     pthread_mutex_unlock(&(handle->lock));
     pthread_mutex_destroy(&(handle->lock));
     pthread_cond_destroy(&(handle->buff_wait));
     if(handle->buffer)free(handle->buffer);
     free(handle);
     return NULL;   
}
int SpeechArrayRead1(SpeechArrayHandle_t *handle, char *buff, int len){
    int ret = 0;
    int skip_data = 0;
    char *data = NULL;
    int read_size = 0;
    int avail_size = 0;
    int check_skip = 0;
    int read_bytes = 0;
    int *temp = (int *)handle->buffer;
    if(handle == NULL || buff == NULL || len<=0 || len%handle->out_align!=0){
        DprintfE("%s failed, bad parameter\n",__FUNCTION__);
        return -1;
    }
    
    pthread_mutex_lock(&(handle->lock));
    if(len > handle->buff_size/handle->ratio){
        len = handle->buff_size/handle->ratio;
    }
    data = (char*)(handle->buffer + handle->data_size);
    avail_size = handle->data_size;
    read_size = (len*handle->ratio - handle->data_size);
    if(read_size%handle->hw_align){
        read_size = read_size + handle->hw_align;
        read_size -= read_size%handle->hw_align;        
    }
    read_bytes = read_size;
    do{
        ret = pcm_read(handle->pcm_handle, data, read_bytes);
        if(ret != 0){
            DprintfE("%s failed, pcm_read error %d\n",__FUNCTION__, ret);
        }else{
            #if DEBUG_DUMP_DATA
            if(dumpfd > 0){
                write(dumpfd,data,read_bytes);
            }
            #endif
            DprintfD("pcm_read %p read %d bytes\n", data, read_bytes);
            avail_size += read_bytes;
            if(!check_skip){
                if((skip_data = skipData(handle->buffer, avail_size)) > 0){
                    memcpy(handle->buffer,(char*)(handle->buffer + skip_data),avail_size-skip_data);
                    data = data + avail_size - skip_data;
                    avail_size -= skip_data;
                    read_bytes = skip_data-skip_data%handle->hw_align + handle->hw_align;
                    check_skip = 1;
                    if(read_bytes){
                        continue;
                    }
                }
            }
            ret = parseData_INT32(handle->buffer, avail_size);
            memcpy(buff, handle->buffer, ret);
            handle->data_size = avail_size - ret*HW_OUT_DATA_RATIO;
            if(handle->data_size){
                memcpy(handle->buffer, (char*)(handle->buffer+ret*HW_OUT_DATA_RATIO), handle->data_size);
                memset((char*)(handle->buffer+handle->data_size),0,ret*HW_OUT_DATA_RATIO);
                #ifdef DEBUG_ARRAY
                DprintfE("align data:%d ", handle->data_size);
                do{
                    printf("0x%08x ",*temp++);   
                }while(*temp != 0);
                printf("0x%08x \n",*temp++);
                #endif
            }    
            break;
        }
    }while(1);
    pthread_mutex_unlock(&(handle->lock));
    return ret;  
}

int SpeechArrayWrite(SpeechArrayHandle_t *handle, char *buff, int len){
    LOCAL_UNUSED(handle);
    LOCAL_UNUSED(buff);
    LOCAL_UNUSED(len);
    return -1;//now no supported
}
int speechArrayClose(SpeechArrayHandle_t *handle){
    int ret = 0;
    if(handle == NULL){
        DprintfE("%s failed, bad parameter\n",__FUNCTION__);
        return -1;
    }
    pthread_mutex_lock(&(handle->lock));
    ret = pcm_close(handle->pcm_handle);
    if(ret < 0){
        DprintfE("%s failed, pcm_close error %d\n",__FUNCTION__, ret);
    }
    pthread_mutex_unlock(&(handle->lock));
    pthread_mutex_destroy(&(handle->lock));
    pthread_cond_destroy(&(handle->buff_wait));
    if(handle->buffer)free(handle->buffer);
    free(handle);
    return 0;
}
int speechArrayUninit(){
    #if DEBUG_DUMP_DATA
    
    if(dumpfd > 0){
        close(dumpfd);
    }
    #endif
    return 0;
}

int SpeechArrayRead(SpeechArrayHandle_t *handle, char *buff, int len){
    int ret = 0;
    int skip_data = 0;
    char *data = NULL;
    int read_size = 0;
    int avail_size = 0;
    int check_skip = 0;
    int read_bytes = 0;
    int parse_size = 0;
    int *temp = (int *)handle->buffer;
    if(handle == NULL || buff == NULL || len<=0 || len%handle->out_align!=0){
        DprintfE("%s failed, bad parameter\n",__FUNCTION__);
        return -1;
    }
    
    pthread_mutex_lock(&(handle->lock));
    
    if(len > handle->buff_size/handle->ratio){
        len = handle->buff_size/handle->ratio;
    }
    data = (char*)(handle->buffer + handle->data_size);
    avail_size = handle->data_size;
    if(avail_size > len*HW_OUT_DATA_RATIO){
        read_size = 0;
    }else{
        read_size = (len*handle->ratio - handle->data_size);
        if(read_size%handle->hw_align){
            read_size = read_size + handle->hw_align;
            read_size -= read_size%handle->hw_align;        
        }
        if(read_size < handle->buff_size/HW_BUFFER_COUNT){
            read_size = handle->buff_size/HW_BUFFER_COUNT;
        }
    }
    
    read_bytes = read_size;
    DprintfE("%s: len:%d, data_size:%d,read_bytes:%d\n",__FUNCTION__,len, handle->data_size,read_bytes);
    do{ 
        if(read_bytes){
            ret = pcm_read(handle->pcm_handle, data, read_bytes);
        }
        if(ret != 0){
            DprintfE("%s failed, pcm_read error %d\n",__FUNCTION__, ret);
        }else{
            #if DEBUG_DUMP_DATA
            if(dumpfd > 0){
                write(dumpfd,data,read_bytes);
            }
            #endif
            DprintfE("pcm_read %p read %d bytes\n", data, read_bytes);
            avail_size += read_bytes;
            if(!check_skip){
                if((skip_data = skipData(handle->buffer, avail_size)) > 0){
                    memcpy(handle->buffer,(char*)(handle->buffer + skip_data),avail_size-skip_data);
                    data = data + avail_size - skip_data;
                    avail_size -= skip_data;
                    if(avail_size >= len*HW_OUT_DATA_RATIO){
                        read_bytes = 0;
                    }else{
                        read_bytes = skip_data-skip_data%handle->hw_align + handle->hw_align;
                        if(read_bytes < handle->buff_size/HW_BUFFER_COUNT){
                            read_bytes = handle->buff_size/HW_BUFFER_COUNT;
                        }
                        if(avail_size+read_size>handle->buff_size){
                            read_bytes = handle->buff_size - avail_size;
                            read_bytes -= read_size%handle->hw_align;
                        }
                    }
                    
                    check_skip = 1;
                    if(read_bytes){
                        continue;
                    }
                }
            }
            
            if(avail_size > len*HW_OUT_DATA_RATIO){
                parse_size = len*HW_OUT_DATA_RATIO;   
            }else{
                parse_size = avail_size;
            }
            ret = parseData_INT32(handle->buffer, parse_size);
            memcpy(buff, handle->buffer, ret);
            handle->data_size = avail_size - parse_size;
            DprintfE("avail_size %d, skip_data:%d,data_size:%d\n", avail_size, skip_data, handle->data_size);
            if(handle->data_size > 0){
                memcpy(handle->buffer, (char*)(handle->buffer+parse_size), handle->data_size);
                memset((char*)(handle->buffer+handle->data_size),0,handle->buff_size-handle->data_size);
                #ifdef DEBUG_ARRAY
                DprintfE("align data:%d ", handle->data_size);
                do{
                    printf("0x%08x ",*temp++);   
                }while(*temp != 0);
                printf("0x%08x \n",*temp++);
                #endif
            }    
            break;
        }
    }while(1);
    pthread_mutex_unlock(&(handle->lock));
    return ret;
}

//#########################################################################
#define CHECK_FORMAT_ERROR 1
#define MINI_SINGLE_SAMPLE_BYTES 48
#if CHECK_FORMAT_ERROR
#define CHECKERROR_INT32_LE(x) (\
        (((*(x    ))&0x00000f00)     != 0x00000100) || \
        (((*(x+1 ))&0x00000f00)      != 0x00000200) || \
        (((*(x+2 ))&0x00000f00)      != 0x00000300) || \
        (((*(x+3 ))&0x00000f00)      != 0x00000400) || \
        (((*(x+4 ))&0x00000f00)      != 0x00000500) || \
        (((*(x+5 ))&0x00000f00)      != 0x00000600) || \
        (((*(x+6 ))&0x00000f00)      != 0x00000700) || \
        (((*(x+7 ))&0x00000f00)      != 0x00000800) || \
        (((*(x+8 ))&0x00000f00)      != 0x00000900) || \
        (((*(x+9 ))&0x00000f00)      != 0x00000a00) || \
        (((*(x+10))&0x00000f00)      != 0x00000b00) || \
        (((*(x+11))&0x00000f00)      != 0x00000c00) \
    )
#endif
#define CHECKDATA_INT32(x) (\
        ((((unsigned int)(*x      ))&0xffff0000) == 0 || (((unsigned int)(*x       ))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+1 )))&0xffff0000) == 0 || (((unsigned int)(*(x+1)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+2 )))&0xffff0000) == 0 || (((unsigned int)(*(x+2)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+3 )))&0xffff0000) == 0 || (((unsigned int)(*(x+3)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+4 )))&0xffff0000) == 0 || (((unsigned int)(*(x+4)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+5 )))&0xffff0000) == 0 || (((unsigned int)(*(x+5)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+6 )))&0xffff0000) == 0 || (((unsigned int)(*(x+6)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+7 )))&0xffff0000) == 0 || (((unsigned int)(*(x+7)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+8 )))&0xffff0000) == 0 || (((unsigned int)(*(x+8)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+9 )))&0xffff0000) == 0 || (((unsigned int)(*(x+9)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+10)))&0xffff0000) == 0 || (((unsigned int)(*(x+10)))&0xffff0000) == 0xffff0000) && \
        ((((unsigned int)(*(x+11)))&0xffff0000) == 0 || (((unsigned int)(*(x+11)))&0xffff0000) == 0xffff0000) \
    )
#define dumpdata_12(msg,pdata) do{\
    DprintfE(msg "0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",\
                *(pdata), *(pdata+1), *(pdata+2), *(pdata+3), *(pdata+4), *(pdata+5), \
                *(pdata+6), *(pdata+7), *(pdata+8), *(pdata+9), *(pdata+10), *(pdata+11)\
    );\
}while(0)

int skipData(char *data, int len){
    unsigned int *pdata = (unsigned int *)data; 
    int skip_data = 0;
    if(len < MINI_SINGLE_SAMPLE_BYTES){
        DprintfE("parseData error: bad parameter\n");
        return -1;
    }
    if(len%MINI_SINGLE_SAMPLE_BYTES != 0){
        len -= len%MINI_SINGLE_SAMPLE_BYTES;    
    }
    do{
        if(*pdata == 0x00000000){
            DprintfE("Invalid data: 0x%08x \n",*pdata);
            skip_data += 4;
            pdata ++;
            continue;
        }
        if(CHECKERROR_INT32_LE(pdata)){
            dumpdata_12("Invalid channel:",pdata);
            skip_data += 4;
            pdata ++;
            continue;
        }
        if(CHECKDATA_INT32(pdata)){
            dumpdata_12("Invalid data:",pdata);
            skip_data += 48;
            pdata += 12;
            continue;
        }
        break;
    }while(skip_data < len);
    return skip_data;
}


/**
 * mini数据格式分析
 * 默认12通道，32bits每个采样点
 * 输出16bits每个采样点，按通道号排列的6个通道数据
 * 数据格式：
 * xxxxx000 xxxxx100 xxxxx200 xxxxx300 xxxxx400 xxxxx500
 * xxxxx600 xxxxx700 xxxxx800 xxxxx900 xxxxxa00 xxxxxb00
 * 其中：1 2 7 8为4路mic数据，4 10位两路aec数据
 * 通道编号从1开始
 */
int parseData_INT32(char *data, int len){
    unsigned int*speech = (unsigned int *)data;
    unsigned int*availspeech = (unsigned int *)data;
    unsigned int*end = NULL;
    int errlen = 0;
    int datalen = 0;
    if(len < MINI_SINGLE_SAMPLE_BYTES){
        DprintfE("parseData error: bad parameter\n");
        return -1;
    }
    if(len%MINI_SINGLE_SAMPLE_BYTES != 0){
        len -= len%MINI_SINGLE_SAMPLE_BYTES;    
    }
    end = (unsigned int *)(speech+len/4);
    
    do{
        #if CHECK_FORMAT_ERROR
        if(CHECKERROR_INT32_LE(speech)){
            //dumpdata_12("ignore error:",speech);
            DprintfE("ignore error:0x%08x\n",*speech);
            speech ++;
            errlen += 4;
            continue; 
        } 
        #endif
        *(availspeech  ) = ((*(speech  ))&0xffff0000)|(((*(speech+1  ))&0xffff0000)>>16);
        *(availspeech+1) = ((*(speech+6))&0xffff0000)|(((*(speech+7  ))&0xffff0000)>>16);
        *(availspeech+2) = ((*(speech+3))&0xffff0000)|(((*(speech+9  ))&0xffff0000)>>16);
        speech += 12;
        availspeech += 3;//MINI_SINGLE_SAMPLE_BYTES/4;
        datalen += MINI_SINGLE_SAMPLE_BYTES;
    }while(speech<end);
    DprintfE("data error len:%d, datalen:%d,len:%d\n",errlen,datalen,len);
    return datalen/4;
}


