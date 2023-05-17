#include "base/x_sorter.h"
#include "base/x_memory.h"
#include "base/x_array.h"

struct x_sorter
{

};

typedef i32_t (*container_iterate_fun)(pt_t container, pt_t element, pt_t arg);

struct x_sorter_funcs
{
  i32_t (*container_iterate)(pt_t container, container_iterate_fun container_iterate_func, pt_t arg);
  i32_t (*container_get_order)(pt_t container, x_compare_func cmp_fn, pt_t arg, u8_t *out_order);
};

/// x_array ///

// container_iterate
struct __x_array_arg_for_container_iterate {
  container_iterate_fun container_iterate_func;
  pt_t arg;
};

static i32_t
__container_iterate_for_x_array_iterate_iterate_fun(x_array_t *array, pt_t element, pt_t arg)
{
  struct __x_array_arg_for_container_iterate *iarg = (struct __x_array_arg_for_container_iterate *)arg;
  return iarg->container_iterate_func(array, element, iarg->arg);
}

static i32_t
__container_iterate_for_x_array(pt_t container, container_iterate_fun container_iterate_func, pt_t arg)
{
  i32_t ret = X_SORTER_OK;
  struct __x_array_arg_for_container_iterate *iarg = (struct __x_array_arg_for_container_iterate *)x_calloc(sizeof(struct __x_array_arg_for_container_iterate), 1);
  iarg->container_iterate_func = container_iterate_func;
  iarg->arg = arg;
  ret = x_array_iterate((x_array_t *)container, __container_iterate_for_x_array_iterate_iterate_fun, iarg);
  x_free(iarg);
  return ret;
}

// container_get_order
struct __x_array_arg_for_get_order {
  bool_t decided;
  bool_t equ_before_decided;
  u8_t out_order;
  pt_t last_element;
  x_compare_func compare_func;
  pt_t arg;
  i32_t cmp;
};

static i32_t
__container_iterate_for_x_array_get_order_iterate_fun(x_array_t *array, pt_t element, pt_t arg)
{
  struct __x_array_arg_for_get_order *iarg = (struct __x_array_arg_for_get_order *)arg;
  if(iarg->last_element) {
    if(X_FALSE == iarg->decided) {
      iarg->cmp = iarg->compare_func(iarg->last_element, element, iarg->arg);
      if (iarg->cmp < 0) {
        iarg->decided = X_TRUE;
        if (X_FALSE == iarg->equ_before_decided) {
          iarg->out_order = X_SORTER_ORDER_ASC;
        } else {
          iarg->out_order = X_SORTER_ORDER_STRICT_ASC;
        }
      } else if (iarg->cmp > 0) {
        iarg->decided = X_TRUE;
        if (X_FALSE == iarg->equ_before_decided) {
          iarg->out_order = X_SORTER_ORDER_DESC;
        } else {
          iarg->out_order = X_SORTER_ORDER_STRICT_DESC;
        }
      } else {
        iarg->equ_before_decided = X_TRUE;
      }
      iarg->last_element = element;
    } else {
      iarg->cmp = iarg->compare_func(iarg->last_element, element, iarg->arg);
      iarg->last_element = element;
      if (iarg->cmp < 0) {
        if (X_SORTER_ORDER_ASC == iarg->out_order || X_SORTER_ORDER_STRICT_ASC == iarg->out_order) {
          // do nothing
        } else {
          iarg->out_order = X_SORTER_ORDER_DISORDER;
          return X_ARRAY_ITERATE_BREAK;
        }
      } else if (iarg->cmp > 0) {
        if (X_SORTER_ORDER_DESC == iarg->out_order || X_SORTER_ORDER_STRICT_DESC == iarg->out_order) {
          // do nothing
        } else {
          iarg->out_order = X_SORTER_ORDER_DISORDER;
          return X_ARRAY_ITERATE_BREAK;
        }
      } else {
        if (X_SORTER_ORDER_ASC == iarg->out_order) {
          iarg->out_order = X_SORTER_ORDER_STRICT_ASC;
        } else if (X_SORTER_ORDER_DESC == iarg->out_order) {
          iarg->out_order = X_SORTER_ORDER_STRICT_DESC;
        }
      }
    }
  }
  return X_SORTER_OK;
}

static i32_t 
__container_get_order_for_x_array(pt_t container, x_compare_func cmp_fn, pt_t arg, u8_t *out_order)
{
  i32_t ret = X_SORTER_OK;
  struct __x_array_arg_for_get_order *iarg = (struct __x_array_arg_for_get_order *)x_calloc(sizeof(struct __x_array_arg_for_get_order), 1);
  if (!CHECK_MEMORY_VAILID(arg)) {
    return X_SORTER_MEMORY_ERROR;
  }
  iarg->decided= X_FALSE;
  iarg->equ_before_decided = X_FALSE;
  iarg->out_order = X_SORTER_ORDER_ASC;
  iarg->last_element = NULL;
  iarg->compare_func = cmp_fn;
  iarg->arg = arg;

  ret = x_array_iterate((x_array_t *)container, __container_iterate_for_x_array_get_order_iterate_fun, iarg);
  (*out_order) = iarg->out_order;
  x_free(iarg);
  return ret;
}

static struct x_sorter_funcs __x_array_sorter_funcs = {
    .container_iterate = __container_iterate_for_x_array,
    .container_get_order = __container_get_order_for_x_array};
/////////////////

i32_t 
x_sorter_create(x_sorter_t **new_sorter)
{
  x_sorter_t *new_sorter_tmp = NULL;

  if (NULL == new_sorter) {
    return X_SORTER_OUT_ARG_IS_NULL;
  }

  new_sorter_tmp = (x_sorter_t *)x_calloc(sizeof(x_sorter_t), 1);
  if (!CHECK_MEMORY_VAILID(new_sorter_tmp)) {
    return X_SORTER_MEMORY_ERROR;
  }

  *new_sorter = new_sorter_tmp;
  return X_SORTER_OK;
}

i32_t 
x_sorter_get_order(x_sorter_t *sorter, u8_t container_type, pt_t container, x_compare_func cmp_fn, pt_t arg, u8_t *out_order)
{
  struct x_sorter_funcs *funs = NULL;
  if (NULL == sorter) {
    return X_SORTER_IS_NULL;
  }

  if (NULL == container) {
    return X_SORTER_BAD_ARG;
  }

  if (NULL == cmp_fn) {
    return X_SORTER_BAD_ARG;
  }

  if (NULL == out_order) {
    return X_SORTER_OUT_ARG_IS_NULL;
  }

  if ( X_SORTER_CONTAINER_TYPR_X_ARRAY == container_type) {
    funs = &__x_array_sorter_funcs;
  }

  return funs->container_get_order(container, cmp_fn, arg, out_order);
}
