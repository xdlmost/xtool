#include "base/x_rbtree.h"
#include "base/x_memory.h"
#include "base/log.h"

#define RB_NODE_COLOR_RED   0
#define RB_NODE_COLOR_BLACK 1

typedef struct x_rbnode {
  i32_t data;
  u8_t color;
  struct x_rbnode *parent;
  struct x_rbnode *left;
  struct x_rbnode *right;
} x_rbnode;

struct x_rbtree {
  x_rbnode *root;
  u32_t count;
  u32_t height;
};

i32_t 
x_rbtree_create(x_rbtree_t **new_rbtree)
{
  i32_t ret = X_RETREE_OK;
  x_rbtree_t *rbtree = NULL;

  if (!new_rbtree){
    ret = X_RETREE_OUT_ARG_IS_NULL;
    goto error;
  }

  rbtree = (x_rbtree_t *)x_calloc(sizeof(x_rbtree_t), 1);
  if (!CHECK_MEMORY_VAILID(rbtree)) {
    ret = X_RETREE_MEMORY_ERROR;
    goto error;
  }
  *new_rbtree = rbtree;

error:
  return ret;
}

void
__x_rbtree_destroy_node(x_rbnode *node)
{
  if (node->left){
    __x_rbtree_destroy_node(node->left);
  }
  if (node->right){
    __x_rbtree_destroy_node(node->right);
  }
  x_free(node);
}

i32_t 
x_rbtree_destroy(x_rbtree_t *rbtree)
{
  if (rbtree->root){
    __x_rbtree_destroy_node(rbtree->root);
    rbtree->root = NULL;
  }
  return X_RETREE_OK;
}

i32_t
__x_rbtree_check_node(x_rbtree_t *rbtree, x_rbnode *node, i32_t black_count)
{
  i32_t ret = X_RETREE_OK;
  if ( RB_NODE_COLOR_RED == node->color) {
    if (!node->parent) {
      ret = X_RETREE_ROOT_IS_NOT_BLACK;
      goto error;
    }

    if (RB_NODE_COLOR_RED == node->parent->color) {
      ret = X_RETREE_RED_NODE_HAS_RED_CHILD;
      goto error;
    }
  }

  if((NULL == node->left) && (NULL == node->right)) {
    i32_t black_count_calc = 0;
    x_rbnode *current = node;
    while(current) {
      if (RB_NODE_COLOR_BLACK == current->color) {
        black_count_calc++;
      }
      current = current->parent;
    }

    if (black_count_calc != black_count) {
      ret = X_RETREE_NOT_ERERY_PATH_HAS_SAME_BLACK_NODE;
      goto error;
    }
  }

  if (node->left){
    ret = __x_rbtree_check_node(rbtree, node->left, black_count);
    if (X_RETREE_OK != ret) {
      goto error;
    }
  }

  if (node->right){
    ret = __x_rbtree_check_node(rbtree, node->right, black_count);
    if (X_RETREE_OK != ret) {
      goto error;
    }
  }
error:
  return ret;
}

i32_t 
x_rbtree_check(x_rbtree_t *rbtree)
{
  i32_t ret = X_RETREE_OK;
  if (rbtree->root) {
    x_rbnode *root = rbtree->root;
    x_rbnode *current = root;
    i32_t black_count = 0;
    if (RB_NODE_COLOR_BLACK != root->color) {
      ret = X_RETREE_ROOT_IS_NOT_BLACK;
      goto error;
    }

    while(current){
      if (RB_NODE_COLOR_BLACK == current->color) {
        black_count++;
      }
      current = current->left;
    }
    return __x_rbtree_check_node(rbtree, root, black_count);
  }

error:
  return ret;
}

// Function performing right rotation
// of the passed node
void 
__x_rbtree_right_rotate(x_rbtree_t *rbtree, struct x_rbnode* temp)
{
    struct x_rbnode* left = temp->left;
    temp->left = left->right;
    if (temp->left)
        temp->left->parent = temp;
    left->parent = temp->parent;
    if (!temp->parent) {
        rbtree->root = left;
        rbtree->root->parent = NULL;  
    }
    else if (temp == temp->parent->left)
        temp->parent->left = left;
    else
        temp->parent->right = left;
    left->right = temp;
    temp->parent = left;
}
 
// Function performing left rotation
// of the passed node
void 
__x_rbtree_left_rotate(x_rbtree_t *rbtree, struct x_rbnode* temp)
{
    struct x_rbnode* right = temp->right;
    temp->right = right->left;
    if (temp->right)
        temp->right->parent = temp;
    right->parent = temp->parent;
    if (!temp->parent) {
      rbtree->root = right;
      rbtree->root->parent = NULL;  
    }

    else if (temp == temp->parent->left)
        temp->parent->left = right;
    else
        temp->parent->right = right;
    right->left = temp;
    temp->parent = right;
}

x_rbnode* 
__x_rbnode_create(i32_t data)
{
  x_rbnode *node = NULL;
  node = (x_rbnode *)x_calloc(sizeof(x_rbnode), 1);
  node->data = data;
  node->color = RB_NODE_COLOR_RED;
}

i32_t 
x_rbtree_insert(x_rbtree_t *rbtree, i32_t data)
{
  i32_t ret = X_RETREE_OK;
  x_rbnode *node_to_insert = __x_rbnode_create(data);
  if (NULL == rbtree->root) {
    node_to_insert->color = RB_NODE_COLOR_BLACK;
    rbtree->root = node_to_insert;
    rbtree->height = 1;
  } else {
    // find parent and insert
    x_rbnode *parent = rbtree->root;
    while(1){
      i32_t cmp = data - parent->data;
      if (cmp > 0){
        if (parent->right){
          parent = parent->right;
        } else {
          parent->right = node_to_insert;
          node_to_insert->parent = parent;
          break;
        }
      } else if (cmp < 0) {
        if (parent->left){
          parent = parent->left;
        } else {
          parent->left = node_to_insert;
          node_to_insert->parent = parent;
          break;
        }
      } else {
        ret = X_RETREE_KEY_DUPLICATED;
        goto error;
      }
    }

    // reblance
    {
      x_rbnode *uncle = NULL;
      x_rbnode *grandp = parent->parent;
      x_rbnode *x = node_to_insert;
      while ((x != rbtree->root) && (RB_NODE_COLOR_BLACK != x->color) && (RB_NODE_COLOR_RED == x->parent->color))
      {
        parent = x->parent;
        grandp = parent->parent;
        /*  Case : A
                  Parent of pt is left child
                  of Grand-parent of x */
        if (parent == grandp->left) {
          struct x_rbnode* uncle = grandp->right;
 
          /* Case : 1
              The uncle of pt is also red
              Only Recoloring required */
          if (uncle != NULL && RB_NODE_COLOR_RED == uncle->color){
              grandp->color = RB_NODE_COLOR_RED;
              parent->color = RB_NODE_COLOR_BLACK;
              uncle->color = RB_NODE_COLOR_BLACK;
              x = grandp;
          } else {

            /* Case : 2
                 x is right child of its parent
                 Left-rotation required */
            if (x == parent->right) {
              __x_rbtree_left_rotate(rbtree, parent);
              x = parent;
              parent = x->parent;
            }
 
            /* Case : 3
                 pt is left child of its parent
                 Right-rotation required */
            __x_rbtree_right_rotate(rbtree, grandp);
            u8_t color = parent->color;
            parent->color = grandp->color;
            grandp->color = color;
            x = parent;
          }
        } else {
          /* Case : B
                Parent of pt is right
                child of Grand-parent of x */
          struct x_rbnode* uncle = grandp->left;
 
          /*  Case : 1
              The uncle of pt is also red
              Only Recoloring required */
          if ((uncle != NULL) && (uncle->color == RB_NODE_COLOR_RED))
          {
              grandp->color = RB_NODE_COLOR_RED;
              parent->color = RB_NODE_COLOR_BLACK;
              uncle->color = RB_NODE_COLOR_BLACK;
              x = grandp;
          }
          else {
              /* Case : 2
                 pt is left child of its parent
                 Right-rotation required */
              if (x == parent->left) {
                  __x_rbtree_right_rotate(rbtree, parent);
                  x = parent;
                  parent = x->parent;
              }
 
              /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
              __x_rbtree_left_rotate(rbtree, grandp);
              u8_t color = parent->color;
              parent->color = grandp->color;
              grandp->color = color;
              x = parent;
          }
        }
      }

      if (x == rbtree->root) {
        rbtree->root->color = RB_NODE_COLOR_BLACK;
        rbtree->height++;
      }
    }
  }
  rbtree->count++;
error:
  return ret;
}

i32_t 
__x_rbtree_inorder_node(x_rbtree_t *rbtree, struct x_rbnode* node, x_rbtree_iterate_fun iterate_fun ,pt_t arg, i32_t *pindex, i32_t level)
{
  if (node){
    __x_rbtree_inorder_node(rbtree, node->left, iterate_fun, arg, pindex, level+1);
    iterate_fun(rbtree, (*pindex)++, level, node->data, arg);
    __x_rbtree_inorder_node(rbtree, node->right, iterate_fun, arg, pindex, level+1);
  }
  return X_RETREE_OK;
}

i32_t 
x_rbtree_inorder_iterate(x_rbtree_t *rbtree, x_rbtree_iterate_fun iterate_fun ,pt_t arg)
{
  i32_t index = 0;
  return __x_rbtree_inorder_node(rbtree, rbtree->root, iterate_fun, arg, &index, 0);
}


i32_t 
x_rbtree_get_height(x_rbtree_t *rbtree)
{
  return rbtree->height;
}