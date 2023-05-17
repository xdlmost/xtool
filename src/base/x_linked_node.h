/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_LINKED_NODE_H
#define __X_LINKED_NODE_H 1
#include "predefine.h"
__X_BEGIN_DECLS

// x_array status
#define X_LINKED_NODE_OK 0
#define X_LINKED_NODE_OUT_ARG_IS_NULL 1
#define X_LINKED_NODE_CREATE_WITH_BAD_LINK_COUNT 2
#define X_LINKED_NODE_MEMORY_ERROR 3
#define X_LINKED_NODE_IS_NULL 4
#define X_LINKED_NODE_DATA_ALREADY_EXIST 5
#define X_LINKED_NODE_BAD_LINK_INDEX 6


typedef struct x_linked_node x_linked_node_t;

/**
 * @brief 
 * 
 * @param link_count 
 * @param new_linked_node 
 * @return i32_t 
 */
X_API i32_t x_linked_node_create(pt_t data, u32_t link_count, x_linked_node_t **new_linked_node);

X_API i32_t x_linked_node_get_data(x_linked_node_t *linked_node, pt_t *out_data);

X_API i32_t x_linked_node_set_data(x_linked_node_t *linked_node, pt_t data);

X_API i32_t x_linked_node_get_link_count(x_linked_node_t *linked_node, u32_t *link_count);

X_API i32_t x_linked_node_get_link_at(x_linked_node_t *linked_node, u32_t index, x_linked_node_t **out_linked_node);

X_API i32_t x_linked_node_set_link_at(x_linked_node_t *linked_node, u32_t index, x_linked_node_t *linked_node_set);

X_API i32_t x_linked_node_swap_link_at(x_linked_node_t *linked_node, u32_t index, x_linked_node_t *linked_node_new, x_linked_node_t **out_old_linked_node);

__X_END_DECLS
#endif //__X_LINKED_NODE_H