#include "xdefs/xdefs.h"
#include "xbase/logger/logger.h"
#include "xbase/mem/xmalloc.h"
#include <stdarg.h>
#include <stdio.h>

struct __logger{
    int32 log_object;
    void (*append)(const char *format, va_list args);
    void (*release)(void);
};

static void stdout_append(const char *format, va_list args){
    vfprintf(stdout, format, args);
}

xret 
create_logger(int32 log_object, logger **newlogger)
{
    if (LOG_OBJECT_DFAULT == log_object){
        (*newlogger) = xmalloc(sizeof(logger));
        (*newlogger)->log_object = LOG_OBJECT_DFAULT;
        (*newlogger)->append = &stdout_append;
        (*newlogger)->release = NULL;
        return XRET_OK;
    }
    return XRET_UNKNOW_LOG_ENUM;
}

xret free_logger(logger *logger)
{
    if (!logger)
        return XRET_NULL_PARAMETER;
    if (logger->release){
        logger->release();
    }
    xfree(logger);
    return XRET_OK;
}

void logger_append(logger *logger, const char* format, ...){
    if (logger && logger->append){
        va_list	args;
        va_start(args, format);
        logger->append(format, args);
        va_end(args);   
    }
}

