/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/


#ifndef __PREDEFINE_H
#define __PREDEFINE_H 1

#ifdef  __cplusplus
# define __X_BEGIN_DECLS  extern "C" {
# define __X_END_DECLS    }
#else
# define __X_BEGIN_DECLS
# define __X_END_DECLS
#endif

#ifdef __PLATFORM_OS_WINDOWS
  #define HELPER_IMPORT __declspec(dllimport)
  #define HELPER_EXPORT __declspec(dllexport)
  #define HELPER_LOCAL
#else
  #if __GNUC__ >= 4
    #define HELPER_IMPORT extern __attribute__ ((visibility ("default")))
    #define HELPER_EXPORT extern __attribute__ ((visibility ("default")))
    #define HELPER_LOCAL  extern __attribute__ ((visibility ("hidden")))
  #else
    #define HELPER_IMPORT extern
    #define HELPER_EXPORT extern
    #define HELPER_LOCAL  extern
  #endif
#endif

#ifdef EXPORT_API // defined if FOR is compiled as a DLL
  #define X_API HELPER_EXPORT
#else
  #ifdef IMPORT_API
    #define X_API HELPER_IMPORT
  #else
    #define X_API HELPER_LOCAL
  #endif
#endif
#define X_LOCAL HELPER_LOCAL

#ifdef __GNUC__
#define X_ATTRIBUTE(X) __attribute__(X)
#else
#define X_ATTRIBUTE(X)
#endif

#ifndef NULL
#define NULL                     0 
#endif

// types
typedef unsigned char             uchar_t;

#if __CHAR_UNSIGNED__ == 1
typedef signed char               i8_t;
#else
typedef char                      i8_t;
#endif

typedef unsigned char             u8_t;
typedef short                     i16_t;
typedef unsigned short            u16_t;
typedef int                       i32_t;
typedef unsigned int              u32_t;
typedef unsigned long long        u64_t;
typedef long long                 i64_t;

typedef char *                    str;
typedef const char *              cstr;


typedef void *                    pt;
typedef const void *              cpt;

typedef u32_t                     ret_t;
typedef uchar_t                   bool_t;
typedef u64_t                     xtime ;


#define X_FALSE                     0
#define X_TRUE                      1

#endif //__PREDEFINE_H