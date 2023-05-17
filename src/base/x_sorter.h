/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_SORTER_H
#define __X_SORTER_H 1
#include "predefine.h"
#include "base/x_compare_funs.h"
__X_BEGIN_DECLS

typedef struct x_sorter x_sorter_t;

#define X_SORTER_OK 0
#define X_SORTER_OUT_ARG_IS_NULL 1
#define X_SORTER_MEMORY_ERROR 2
#define X_SORTER_IS_NULL 3
#define X_SORTER_BAD_ARG 4


#define X_SORTER_ORDER_ASC 0
#define X_SORTER_ORDER_DESC 1
#define X_SORTER_ORDER_STRICT_ASC 2
#define X_SORTER_ORDER_STRICT_DESC 3
#define X_SORTER_ORDER_DISORDER 4


#define X_SORTER_INSERTINO 0

#define X_SORTER_CONTAINER_TYPR_X_ARRAY 0



X_API i32_t x_sorter_create(x_sorter_t **new_sorter);

X_API i32_t x_sorter_get_order(x_sorter_t *sorter, u8_t container_type, pt_t container, x_compare_func cmp_fn, pt_t arg, u8_t *out_order);




__X_END_DECLS
#endif //__X_SORTER_H