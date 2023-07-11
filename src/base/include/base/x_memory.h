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
 * @return pt_t out memory pointer 
 */
X_API(pt_t) x_malloc(u32_t ele_size);

/**
 * @brief this will allocate new memory with zero-set data
 * 
 * @param ele_size element size by byte
 * @param ele_count element count
 * @return pt_t out memory pointer 
 */
X_API(pt_t) x_calloc(u32_t ele_size, u32_t ele_count);

/**
 * @brief this will re-allocate new memory with old data and random data(initialized data)
 * 
 * @param mem old memory pointer, after realloc this pointer will be released
 * @param new_size new size by byte
 * @return pt_t out memory pointer 
 */
X_API(pt_t) x_realloc(pt_t mem, u32_t new_size);

/**
 * @brief free memory pointer created by x_malloc\x_calloc\x_realloc
 * 
 * @param mem memory pointer to free
 * @return void
 */
X_API(void) x_free(pt_t mem);

/**
 * @brief copy memory from source to destination with count
 * 
 * @param dest destination pointer
 * @param src source pointer
 * @param count copy count
 * @return pt_t out memory pointer 
 */
X_API(pt_t) x_memcpy(pt_t dest, cpt_t src, u32_t count);

/**
 * @brief copy memory from source to destination with count, it works when source and destination have some overlap
 * 
 * @param dest destination pointer
 * @param src source pointer
 * @param count copy count
 * @return pt_t out memory pointer  
 */
X_API(pt_t) x_memmove(pt_t dest, cpt_t src, u32_t count);

/**
 * @brief set destination with repeated value fill to count
 * 
 * @param dest destination pointer
 * @param val the repeated value set to
 * @param count set count 
 * @return pt_t out memory pointer   
 */
X_API(pt_t) x_memset(pt_t dest, int val, u32_t count);

/**
 * @brief set destination with zero fill to count
 * 
 * @param dest destination pointer
 * @param count set count 
 * @return pt_t out memory pointer   
 */
X_API(pt_t) x_memzero(pt_t dest, u32_t count);

/**
 * @brief compare cmp1 and cmp2 with count, if cmp1 and cmp2 are the same by bytes within count return 0
 * 
 * @param cmp1 cmp1 pointer
 * @param cmp2 cmp2 pointer
 * @param count compare count
 * @return if cmp1 and cmp2 are the same by bytes within count return 0 
 */
X_API(int) x_memcmp(cpt_t cmp1, cpt_t cmp2, u32_t count);
__X_END_DECLS
#endif //__X_MEMORY_H