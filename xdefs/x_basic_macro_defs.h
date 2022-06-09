#ifndef X_MACRO_DEFS_H
#define X_MACRO_DEFS_H

#ifdef  __cplusplus
# define __X_BEGIN_DECLS  extern "C" {
# define __X_END_DECLS    }
#else
# define __X_BEGIN_DECLS
# define __X_END_DECLS
#endif


#ifdef _WINDOWS
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

#endif