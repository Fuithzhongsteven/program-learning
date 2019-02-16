/*
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdarg.h>

#include "dprintf.h"

#if 0
static int64_t getSystemTime()
{
    struct timespec t;
    t.tv_sec = t.tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (int64_t)(t.tv_sec)*1000000000LL + t.tv_nsec;
}
#endif

static char* sysTimeStr() 
{ 
    struct timeval tv; 
    struct timezone tz;   
    struct tm         *p; 
    char buffer[24] = {0};   
    gettimeofday(&tv, &tz);  
    p = localtime(&tv.tv_sec); 
    //DprintfD("time_now:%d%d%d%d%d%d.%ld\n", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec); 
    sprintf(buffer,"%04d%02d%02d%02d%02d%02d:%03ld",
        p->tm_year+1900,p->tm_mon,p->tm_mday,
        p->tm_hour,p->tm_min,p->tm_sec,tv.tv_usec/1000);
    buffer[18] = '\0';
    //printf("time_now:%s\n",buffer);
    return strdup(buffer);
}


inline int _dprintf(const char *fmt, ...)
{
	char ts_buf[4096+20];
	int err;
    char *p = ts_buf;
    
    char *pStrNow = sysTimeStr();
	sprintf(p, "[%s] ", pStrNow);
    p = ts_buf + strlen(pStrNow)+3;
    if(pStrNow)free(pStrNow);

	va_list ap;
	va_start(ap, fmt);
	err = vsnprintf(p, 4096, fmt, ap);
	va_end(ap);

	printf("%s", ts_buf);

	return err;
}



