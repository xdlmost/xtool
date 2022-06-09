
#include "xbase/common/xtime.h"
#ifdef _WINDOWS
#include <time.h>
#include <Windows.h>
#include <stdio.h>

xtime 
xtime_now(){
    SYSTEMTIME wtm;
    time_t clock;
    struct tm tm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    xtime timestamp = clock * 1000000 + wtm.wMilliseconds * 1000;
    return timestamp;
}

void xtime_now_str(char str[128]){
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d.%06d", wtm.wYear, wtm.wMonth, wtm.wDay, wtm.wHour, wtm.wMinute, wtm.wSecond, wtm.wMilliseconds * 1000);
}

#else
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
xtime 
xtime_now(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    xtime timestamp = tv.tv_sec * 1000000 + tv.tv_usec;
    return timestamp;
}

void xtime_now_str(char str[128]){
    struct timeval tv;
    struct tm tm_time;
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_time);
    sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d.%06d", tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, tv.tv_usec);
}
#endif