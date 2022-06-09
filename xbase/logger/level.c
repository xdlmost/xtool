#include <stdio.h>
#include <string.h>
#include "xbase/logger/level.h"
#ifdef _WINDOWS
#define strncasecmp strnicmp
#endif

static const char* const levels[] = {
    "UNKNOWN",
    "FATAL", 
    "ALERT",
    "CRIT",
    "ERROR",
    "WARN",
    "NOTICE",
    "INFO",
    "DEBUG",
    "TRACE",
};

static const size_t nlevels = sizeof(levels) / sizeof(levels[0]);

/*******************************************************************************/
const char* 
x_level_to_string(int32 a_level)
{
    int32 i ;
    if (a_level <1) {
        a_level = 0;
        return levels[a_level];
    }
	for (i = 1; i < nlevels; i++) {
        if ( (1<<(i-1)) == a_level) {
            return levels[i];
        }
	}
    return levels[0];
}    

/*******************************************************************************/
int32 
x_level_to_int(const char* a_level_name)
{
    int32 i; 

    if (a_level_name) {
	for (i = 1; i < nlevels; i++) {
	    if (!strncasecmp(levels[i], a_level_name, strlen(levels[i])))
		return 1 << (i-1) ;
	}
    }
    
    return 0;
}    

