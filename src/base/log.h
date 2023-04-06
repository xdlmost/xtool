/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __LOG_H
#define __LOG_H 1
#include "predefine.h"
__X_BEGIN_DECLS

#define LOG_PERFIX  __FUNCTION__, __FILE__, __LINE__
#define LOG_TYPE_DEBUG 'D'
#define LOG_TYPE_ERROR 'E'

#define LOG_DEBUG(...) __x_log_(LOG_TYPE_DEBUG, LOG_PERFIX, __VA_ARGS__)
#define LOG_ERROR(...) __x_log_(LOG_TYPE_ERROR, LOG_PERFIX, __VA_ARGS__)

X_API void __x_log_(char type, cstr func_name, cstr file_name, u32_t line, cstr format, ...);

__X_END_DECLS
#endif //__LOG_H