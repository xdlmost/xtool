/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_MEMORY_H
#define __X_MEMORY_H 1
#include "base/predefine.h"
__X_BEGIN_DECLS

X_API pt x_malloc(u32_t ele_size);
X_API pt x_calloc(u32_t ele_size, u32_t ele_count);
X_API pt x_realloc(pt mem, u32_t new_size);
X_API void x_free(pt mem);

__X_END_DECLS
#endif //__X_MEMORY_H