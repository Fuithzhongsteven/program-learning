/*
* Copyright (c) 2017, 深圳市优必选科技有限公司
* All rights reserved.
*
* 文件名称：UBTSpeechPersistent.h
* 创建时间：2018/11/26
* 文件标识：
* 文件摘要：语音存储接口
*
* 当前版本：1.0.0.0
* 作    者：steven
* 完成时间：2018/11/26
* 版本摘要：
*/
#ifndef UBTSPEECHPERSISTENT_H
#define UBTSPEECHPERSISTENT_H

#if defined(__cplusplus)
extern "C" {
#endif


typedef enum {
    TYPE_START,
    TYPE_SEEPCH,
    TYPE_ASR,
    TYPE_NLP,
    TYPE_STOP,
} PersistentType_t;

/**
 * 函数名: Init
 * 功能: 初始化服务
 * 参数: void*
 * 返回值: void
 * 时间: 2018/11/26
 */
extern void Init(void*param);
extern void* speechStart();
extern int speechProcess(void* handle,char *buf, int len, PersistentType_t type);
extern int speechStop(void* handle, int isCompleted);
extern void unInit();

#if defined(__cplusplus)
}
#endif

#endif

