#ifndef __SPEECHARRAY_H_
#define __SPEECHARRAY_H_

#if defined(__cplusplus)
extern "C" {
#endif
typedef enum {
    WorkMode_MicArray, //从mic阵列读取数据模式，当前只支持这种模式
    WorkMode_File,     //从录音文件读取数据
    WorkMode_Inject,   //loop模式，放回write下去的处理后的原始音频
    WorkMode_Others,   //其它模式，
}WorkMode_e;

struct SpeechArray_t{
    WorkMode_e mode;        //工作模式
    int issync;             //接口同步还是异步模式，当前只支持同步模式
    
    unsigned int card;      //声卡标号
    unsigned int device;    //设备编号
    unsigned int channels;  //通道数
    unsigned int rate;      //采样率
    unsigned int period_size;
    unsigned int period_count;
    unsigned int format;    //数据格式
};

//extern 
struct SpeechArrayHandle_t;
typedef struct SpeechArray_t SpeechArray_t;
typedef struct SpeechArrayHandle_t SpeechArrayHandle_t;
/**
 * 语音库初始化
 */
extern int speechArrayInit();
/**
 * 打开语音库和mic阵列
 * config： mic阵列的配置参数
 * 返回值：打开成功返回对应的handle，打开失败返回NULL
 */
extern SpeechArrayHandle_t *speechArrayOpen(SpeechArray_t *config);
/**
 * 读取mic阵列的数据
 * handle：mic阵列对应的句柄
 * buff：读取的数据buffer，用来存放读取的数据
 * len：读取数据的buffer长度
 * 返回值：成功返回读取的自己数，失败返回<0
 */
extern int SpeechArrayRead(SpeechArrayHandle_t *handle, char *buff, int len);
/**
 * 向mic阵列写数据，实现loop模式，当前不支持
 */
extern int SpeechArrayWrite(SpeechArrayHandle_t *handle, char *buff, int len);
/**
 * 关闭mic阵列，释放相关资源
 * handle：mic阵列对应的句柄
 * 返回值：成功返回0 ，失败返回<0
 */
extern int speechArrayClose(SpeechArrayHandle_t *handle);
/**
 * 反初始化语音库
 * 返回值：成功返回0 ，失败返回<0
 */
extern int speechArrayUninit();

#if defined(__cplusplus)
}  /* extern "C" */
#endif

#endif
