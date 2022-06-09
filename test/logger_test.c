#include "xdefs/xdefs.h"
#include "xbase/xarray.h"
#include "xbase/logger/logger.h"
#include <stdio.h>

int main(int argc, char** args)
{
    logger *logger = NULL;
    uchar uc = 58;
    int8 i8 = 8;
    uint8 u8 = 16;
    int16 i16 = -36;
    uint16 u16 = 76;
    int32 i32 = 128;
    uint32 u32 = 129;
    int64 i64 = 8956;
    uint64 u64 = 89564;
    str sstr= "hehe";
    cstr scstr= "hedsadsahe";
    pt p = 456;

    create_logger(LOG_OBJECT_DFAULT, &logger);
    LOGGER_APPEND(logger, X_LEVEL_FATAL, "uchar(58)--%c", uc);
    LOGGER_APPEND(logger, X_LEVEL_ALERT, "int8(8)--%d", i8);
    LOGGER_APPEND(logger, X_LEVEL_CRIT, "uint8(16)--%u", u8);
    LOGGER_APPEND(logger, X_LEVEL_ERROR, "int16(-36)--%d", i16);
    LOGGER_APPEND(logger, X_LEVEL_WARN, "uint16(76)--%u", u16);
    LOGGER_APPEND(logger, X_LEVEL_NOTICE, "int32(128)--%d", i32);
    LOGGER_APPEND(logger, X_LEVEL_INFO, "uint32(129)--%u", u32);
    LOGGER_APPEND(logger, X_LEVEL_DEBUG, "int64(8956)--%ld", i64);
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "uint64(89564)--%lu", u64);
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "str(hehe)--%s", sstr);
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "cstr(hedsadsahe)--%s", scstr);
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "pt(456)--%p", p);
    LOGGER_APPEND0(logger, X_LEVEL_TRACE, "");
    LOGGER_APPEND0(logger, X_LEVEL_TRACE, "");
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(uchar)--%d", sizeof(uchar));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(int8)--%d", sizeof(int8));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(uint8)--%d", sizeof(uint8));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(int16)--%d", sizeof(int16));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(uint16)--%d", sizeof(uint16));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(int32)--%d", sizeof(int32));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(uint32)--%d", sizeof(uint32));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(int64)--%d", sizeof(int64));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(uint64)--%d", sizeof(uint64));
    LOGGER_APPEND(logger, X_LEVEL_TRACE, "sizeof(pt)--%d", sizeof(pt));
    return 0;
}