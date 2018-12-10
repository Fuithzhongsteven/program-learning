/*
* Copyright (c) 2017, steven.zhong
* All rights reserved.
*
* 文件名称：dprintf.h
* 创建时间：2018/12/06
* 文件标识：
* 文件摘要：调试函数接口
*
* 当前版本：1.0.0.0
* 作    者：steven
* 完成时间：2018/11/26
* 版本摘要：
*/
#ifndef DPRINTF_H
#define DPRINTF_H

#if defined(__cplusplus)
extern "C" {
#endif

#define DEBUG_EMERG	    0
#define DEBUG_ALERT	    1
#define DEBUG_CRIT	    2
#define DEBUG_ERR	    3
#define DEBUG_WARNING	4
#define DEBUG_NOTICE	5
#define DEBUG_INFO	    6
#define DEBUG_DEBUG	    7

//#define DEBUG_LIB
#if defined(DEBUG_LIB)
#define DEBUGLEVEL DEBUG_DEBUG
#else
#define DEBUGLEVEL DEBUG_WARNING
#endif

extern int _dprintf(const char *fmt, ...);

#define DprintfD(x...) do { if ((DEBUG_DEBUG)   <= DEBUGLEVEL) { _dprintf(x); } } while (0)
#define DprintfI(x...) do { if ((DEBUG_INFO)    <= DEBUGLEVEL) { _dprintf(x); } } while (0)
#define DprintfN(x...) do { if ((DEBUG_NOTICE)  <= DEBUGLEVEL) { _dprintf(x); } } while (0)
#define DprintfW(x...) do { if ((DEBUG_WARNING) <= DEBUGLEVEL) { _dprintf(x); } } while (0)
#define DprintfE(x...) do { if ((DEBUG_ERR)     <= DEBUGLEVEL) { _dprintf(x); } } while (0)
#define DprintfC(x...) do { if ((DEBUG_CRIT)    <= DEBUGLEVEL) { _dprintf(x); } } while (0)
#define DprintfA(x...) do { if ((DEBUG_ALERT)   <= DEBUGLEVEL) { _dprintf(x); } } while (0)

#define Dprintf(level, x...)  do { if ((level)  <= DEBUGLEVEL) { _dprintf(x); } } while (0)


#if defined(__cplusplus)
}
#endif

#endif

