#include "base/x_linked_node.h"
#include "base/x_memory.h"

struct x_linked_node
{
  pt_t data;
  u32_t link_count;
  x_linked_node_t *links[0];
};

i32_t 
x_linked_node_create(pt_t data, u32_t link_count, x_linked_node_t **new_linked_node)
{
  x_linked_node_t *new_node = NULL;
  if (0 == link_count) {
    return X_LINKED_NODE_CREATE_WITH_BAD_LINK_COUNT;
  }

  if (NULL == new_linked_node) {
    return X_LINKED_NODE_OUT_ARG_IS_NULL;
  }

  new_node = (x_linked_node_t *)x_calloc(sizeof(x_linked_node_t) + sizeof(x_linked_node_t *) * link_count, 1);
  if (!CHECK_MEMORY_VAILID(new_node)) {
    return X_LINKED_NODE_MEMORY_ERROR;
  }

  new_node->data = data;
  new_node->link_count = link_count;
  *new_linked_node = new_node;
  return X_LINKED_NODE_OK;
}

i32_t 
x_linked_node_get_data(x_linked_node_t *linked_node, pt_t *out_data)
{
  if (NULL == linked_node) {
    return X_LINKED_NODE_IS_NULL;
  }

  if (NULL == out_data) {
    return X_LINKED_NODE_OUT_ARG_IS_NULL;
  }

  *out_data = linked_node->data;
  return X_LINKED_NODE_OK;
}

i32_t 
x_linked_node_set_data(x_linked_node_t *linked_node, pt_t data)
{
  if (NULL == linked_node) {
    return X_LINKED_NODE_IS_NULL;
  }

  if (NULL == linked_node->data) {
    return X_LINKED_NODE_DATA_ALREADY_EXIST;
  }

  linked_node->data = data;
  return X_LINKED_NODE_OK;
}

i32_t 
x_linked_node_get_link_count(x_linked_node_t *linked_node, u32_t *link_count)
{
  if (NULL == linked_node) {
    return X_LINKED_NODE_IS_NULL;
  }

  *link_count = linked_node->link_count;
  return X_LINKED_NODE_OK;
}

i32_t 
x_linked_node_get_link_at(x_linked_node_t *linked_node, u32_t index, x_linked_node_t **out_linked_node)
{
  if (NULL == linked_node) {
    return X_LINKED_NODE_IS_NULL;
  }

  if (index >= linked_node->link_count) {
    return X_LINKED_NODE_BAD_LINK_INDEX;
  }

  if (NULL == out_linked_node) {
    return X_LINKED_NODE_OUT_ARG_IS_NULL;
  }

  *out_linked_node = linked_node->links[index];
  return X_LINKED_NODE_OK;
}

i32_t 
x_linked_node_set_link_at(x_linked_node_t *linked_node, u32_t index, x_linked_node_t *linked_node_set)
{
  if (NULL == linked_node) {
    return X_LINKED_NODE_IS_NULL;
  }

  if (index >= linked_node->link_count) {
    return X_LINKED_NODE_BAD_LINK_INDEX;
  }

  linked_node->links[index] = linked_node_set;
  return X_LINKED_NODE_OK;
}

i32_t x_linked_node_swap_link_at(x_linked_node_t *linked_node, u32_t index, x_linked_node_t *linked_node_new, x_linked_node_t **out_old_linked_node)
{
  if (NULL == linked_node) {
    return X_LINKED_NODE_IS_NULL;
  }

  if (index >= linked_node->link_count) {
    return X_LINKED_NODE_BAD_LINK_INDEX;
  }

  if(out_old_linked_node) {
    *out_old_linked_node = linked_node->links[index];
  }

  linked_node->links[index] = linked_node_new;
  return X_LINKED_NODE_OK;
}