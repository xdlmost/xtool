#ifndef X_TIME_H
#define X_TIME_H

#include "xdefs/xdefs.h"
__X_BEGIN_DECLS

typedef struct __x_time x_time_t;


xtime xtime_now();
void xtime_now_str(char str[128]);

__X_END_DECLS

#endif // X_LOGGER_H