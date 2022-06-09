#ifndef LOGGER_H
#define LOGGER_H

#include "xdefs/xdefs.h"
#include "xbase/logger/level.h"
#include "xbase/common/xtime.h"
__X_BEGIN_DECLS

typedef struct __logger logger;

typedef struct 
{
    const char* loc_file;
    int loc_line;
    const char* loc_function;

} x_location_info_t;

#define LOG4C_LOCATION_INFO_INITIALIZER { __FILE__, __LINE__, __FUNCTION__ }

#define LOG_OBJECT_DFAULT 0 

X_LOCAL xret create_logger(int32 log_object, logger **newlogger);
X_LOCAL xret free_logger(logger *logger);
X_LOCAL void logger_append(logger *logger, const char* format, ...);

#define LOGGER_APPEND(logger, level, format, ...) \
    do                                                      \
    {                                                       \
        x_location_info_t loc_info = LOG4C_LOCATION_INFO_INITIALIZER;\
        char time_str[128]={0};                                         \
        xtime_now_str(time_str);                                         \
        logger_append(logger, "[%c|%s|%s:%d(%s)]:" #format "\n", x_level_to_string(level)[0], time_str, loc_info.loc_file, loc_info.loc_line, loc_info.loc_function, ##__VA_ARGS__); \
    } while (0)

#define LOGGER_APPEND0(logger, level, format) \
    do                                                      \
    {                                                       \
        x_location_info_t loc_info = LOG4C_LOCATION_INFO_INITIALIZER;\
        char time_str[128]={0};                                         \
        xtime_now_str(time_str);                                         \
        logger_append(logger, "[%c|%s|%s:%d(%s)]:" #format "\n", x_level_to_string(level)[0], time_str, loc_info.loc_file, loc_info.loc_line, loc_info.loc_function); \
    } while (0)


__X_END_DECLS

#endif // X_LOGGER_H