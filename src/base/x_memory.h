/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_MEMORY_H
#define __X_MEMORY_H 1
#include "base/predefine.h"
__X_BEGIN_DECLS

#define CHECK_MEMORY_VAILID(x) (NULL != x)

/**
 * @brief  this will allocate new memory with random data(initialized data)
 * 
 * @param ele_size element size by byte
 * @return pt out memory pointer 
 */
X_API pt x_malloc(u32_t ele_size);

/**
 * @brief this will allocate new memory with zero-set data
 * 
 * @param ele_size element size by byte
 * @param ele_count element count
 * @return pt out memory pointer 
 */
X_API pt x_calloc(u32_t ele_size, u32_t ele_count);

/**
 * @brief this will re-allocate new memory with old data and random data(initialized data)
 * 
 * @param mem old memory pointer, after realloc this pointer will be released
 * @param new_size new size by byte
 * @return pt out memory pointer 
 */
X_API pt x_realloc(pt mem, u32_t new_size);

/**
 * @brief free memory pointer created by x_malloc\x_calloc\x_realloc
 * 
 * @param mem memory pointer to free
 * @return void
 */
X_API void x_free(pt mem);


__X_END_DECLS
#endif //__X_MEMORY_H