/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_ARRAY_H
#define __X_ARRAY_H 1
#include "predefine.h"
__X_BEGIN_DECLS

// x_array status
#define X_ARRAY_OK 0
#define X_ARRAY_IS_NULL 1
#define X_ARRAY_MEMORY_ERROR 2
#define X_ARRAY_ELEMENT_SIZE_IS_ZERO 3
#define X_ARRAY_CAPACITY_IS_ZREO 4
#define X_ARRAY_IS_FULL 5
#define X_ARRAY_IS_EMPRY 6

typedef struct x_array x_array_t;

X_API i32_t x_create_array(u32_t ele_size, u32_t capacity, x_array_t **new_array);
X_API i32_t x_array_get_capacity(x_array_t *array, u32_t *capacity);
X_API i32_t x_array_get_size(x_array_t *array, u32_t *size);
X_API i32_t x_array_get_element(x_array_t *array, u32_t index, pt *out_ele);
X_API i32_t x_array_push_back_element(x_array_t *array, pt out_ele);
X_API i32_t x_array_pop_back_element(x_array_t *array, pt *out_ele);

__X_END_DECLS
#endif //__X_ARRAY_H