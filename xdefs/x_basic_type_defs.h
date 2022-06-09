#ifndef X_BASIC_TYPE_DEFS_H
#define X_BASIC_TYPE_DEFS_H

typedef unsigned char             uchar;

#if __CHAR_UNSIGNED__ == 1
typedef signed char               int8;
#else
typedef char                      int8;
#endif

typedef unsigned char             uint8;
typedef short                     int16;
typedef unsigned short            uint16;
typedef int                       int32;
typedef unsigned int              uint32;
typedef unsigned long long        uint64;
typedef long long                 int64;

typedef char *                    str;
typedef const char *              cstr;


typedef void *                    pt;
typedef const void *              cpt;

typedef uint32                    xret;
typedef uchar                     bool_t;
typedef uint64                    xtime ;


#define FALSE                     0
#define TRUE                      1

#endif