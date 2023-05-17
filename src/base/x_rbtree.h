/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_RBTREE_H
#define __X_RBTREE_H 1
#include "predefine.h"
__X_BEGIN_DECLS
#define X_RETREE_OK 0
#define X_RETREE_MEMORY_ERROR 1
#define X_RETREE_OUT_ARG_IS_NULL 2
#define X_RETREE_ROOT_IS_NOT_BLACK 3
#define X_RETREE_RED_NODE_HAS_RED_CHILD 4
#define X_RETREE_NOT_ERERY_PATH_HAS_SAME_BLACK_NODE 5
#define X_RETREE_KEY_DUPLICATED 6

typedef struct x_rbtree x_rbtree_t;
typedef i32_t (*x_rbtree_iterate_fun)(x_rbtree_t *rbtree, i32_t index, i32_t level, i32_t data, pt_t arg);

X_API i32_t x_rbtree_create(x_rbtree_t **new_rbtree);

X_API i32_t x_rbtree_destroy(x_rbtree_t *rbtree);

X_API i32_t x_rbtree_check(x_rbtree_t *rbtree);

X_API i32_t x_rbtree_insert(x_rbtree_t *rbtree, i32_t data);

X_API i32_t x_rbtree_inorder_iterate(x_rbtree_t *rbtree, x_rbtree_iterate_fun iterate_fun ,pt_t arg);

X_API i32_t x_rbtree_get_height(x_rbtree_t *rbtree);

__X_END_DECLS
#endif //__X_RBTREE_H