#include "base/x_array.h"
#include "base/x_memory.h"

struct x_array
{
  u32_t ele_size;
  u32_t capacity;
  u32_t size;
  void *eles_data;
};

i32_t 
x_create_array(u32_t ele_size, u32_t capacity, x_array_t **new_array)
{
  i32_t ret = X_ARRAY_OK;
  x_array_t *array = NULL;
  void *eles_data = NULL;
  if (ele_size <= 0) {
    ret = X_ARRAY_ELEMENT_SIZE_IS_ZERO;
    goto error;
  }

  if (capacity <= 0) {
    ret = X_ARRAY_ELEMENT_SIZE_IS_ZERO;
    goto error;
  }

  if (!new_array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  array = (x_array_t *)x_malloc(sizeof(x_array_t));
  if (!CHECK_MEMORY_VAILID(array)) {
    ret = X_ARRAY_MEMORY_ERROR;
    goto error;
  }

  eles_data = x_calloc(ele_size, capacity);
  if (!CHECK_MEMORY_VAILID(eles_data)) {
    ret = X_ARRAY_MEMORY_ERROR;
    goto error;
  }

  array->ele_size = ele_size;
  array->capacity = capacity;
  array->size = 0;
  array->eles_data = eles_data;

  (*new_array) = array;
  return X_ARRAY_OK;
  
error:
  if (eles_data) {
    x_free(eles_data);
    eles_data = NULL; 
  }

  if (array) {
    x_free(array);
    array = NULL; 
  }

  return ret;
}