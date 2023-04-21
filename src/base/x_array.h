/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_ARRAY_H
#define __X_ARRAY_H 1
#include "predefine.h"
__X_BEGIN_DECLS

typedef i32_t (*element_destroy_fun)(void *mem);

// x_array status
#define X_ARRAY_OK 0
#define X_ARRAY_IS_NULL 1
#define X_ARRAY_MEMORY_ERROR 2
#define X_ARRAY_ELEMENT_SIZE_IS_ZERO 3
#define X_ARRAY_CAPACITY_IS_ZREO 4
#define X_ARRAY_IS_FULL 5
#define X_ARRAY_IS_EMPRY 6
#define X_ARRAY_OUT_ARG_IS_NULL 7
#define X_ARRAY_BAD_INDEX 8

typedef struct x_array x_array_t;

/**
 * @brief create an array with element size and capacity
 * 
 * @param ele_size element size by byte
 * @param capacity capacity means array size cannot be bigger than this
 * @param new_array out new array
 * @return X_ARRAY_OK if no error return
 */
X_API i32_t x_array_create(u32_t ele_size, u32_t capacity, x_array_t **new_array);

/**
 * @brief destroy an array
 * 
 * @param array array to destroy
 * @return X_ARRAY_OK if no error return
 */
X_API i32_t x_array_destroy(x_array_t *array);

/**
 * @brief get the capacity of the array
 * 
 * @param array the array to get capacity
 * @param capacity out capacity
 * @return X_ARRAY_OK if no error return 
 */
X_API i32_t x_array_get_capacity(x_array_t *array, u32_t *capacity);

/**
 * @brief get the size of the array
 * 
 * @param array the array to get size
 * @param size out array size
 * @return X_ARRAY_OK if no error return 
 */
X_API i32_t x_array_get_size(x_array_t *array, u32_t *size);

/**
 * @brief get the elements pointer of the array
 * 
 * @param array the array to get elements
 * @param out_eles out array elements pointer
 * @return X_ARRAY_OK if no error return 
 */
X_API i32_t x_array_get_elements(x_array_t *array, pt *out_eles);

/**
 * @brief get element at index
 * 
 * @param array this array to get element
 * @param index the index to get element
 * @param out_ele out element pointer
 * @return X_ARRAY_OK if no error return  
 */
X_API i32_t x_array_get_element_at(x_array_t *array, u32_t index, pt *out_ele);

/**
 * @brief push an element at last 
 * 
 * @param array this array to push
 * @param ele the element to push
 * @return X_ARRAY_OK if no error return 
 */
X_API i32_t x_array_push_back_element(x_array_t *array, pt ele);

/**
 * @brief insert an element at index
 * 
 * @param array this array to insert
 * @param index the index to insert
 * @param ele the element to insert
 * @return X_ARRAY_OK if no error return  
 */
X_API i32_t x_array_insert_element_at(x_array_t *array, u32_t index, pt ele);

/**
 * @brief pop elememt
 * 
 * @param array this array to pop
 * @param out_ele popped elememt
 * @return X_ARRAY_OK if no error return  
 */
X_API i32_t x_array_pop_back_element(x_array_t *array, pt *out_ele);

/**
 * @brief remove element
 * 
 * @param array this array to remove element at index
 * @param index index to remove
 * @param dfun destroy element function if not NULL 
 * @return X_ARRAY_OK if no error return   
 */
X_API i32_t x_array_remove_element_at(x_array_t *array, u32_t index, element_destroy_fun *dfun);

/**
 * @brief clean all elements
 * 
 * @param array this array to clean all elements
 * @param dfun destroy element function if not NULL 
 * @return X_ARRAY_OK if no error return   
 */
X_API i32_t x_array_clean(x_array_t *array, element_destroy_fun *dfun);

__X_END_DECLS
#endif //__X_ARRAY_H