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
x_array_create(u32_t ele_size, u32_t capacity, x_array_t **new_array)
{
  i32_t ret = X_ARRAY_OK;
  x_array_t *array = NULL;
  void *eles_data = NULL;
  if (ele_size <= 0) {
    ret = X_ARRAY_ELEMENT_SIZE_IS_ZERO;
    goto error;
  }

  if (capacity <= 0) {
    ret = X_ARRAY_CAPACITY_IS_ZREO;
    goto error;
  }

  if (!new_array) {
    ret = X_ARRAY_OUT_ARG_IS_NULL;
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

i32_t 
x_array_destroy(x_array_t *array)
{
  i32_t ret = X_ARRAY_OK;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  if (array->eles_data) {
    x_free(array->eles_data);
  }

  if (array) {
    x_free(array);
  }

error:
  return ret;
}

i32_t 
x_array_get_capacity(x_array_t *array, u32_t *capacity)
{
  i32_t ret = X_ARRAY_OK;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }
  if (!capacity) {
    ret = X_ARRAY_OUT_ARG_IS_NULL;
    goto error;
  }

  (*capacity) = array->capacity;
error:
  return ret;
}

i32_t 
x_array_get_size(x_array_t *array, u32_t *size)
{
  i32_t ret = X_ARRAY_OK;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }
  if (!size) {
    ret = X_ARRAY_OUT_ARG_IS_NULL;
    goto error;
  }

  (*size) = array->size;
error:
  return ret;
}


i32_t 
x_array_get_elements(x_array_t *array, pt *out_eles)
{
  i32_t ret = X_ARRAY_OK;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }
  if (!out_eles) {
    ret = X_ARRAY_OUT_ARG_IS_NULL;
    goto error;
  }

  (*out_eles) = array->eles_data;
error:
  return ret;
}

i32_t 
x_array_get_element_at(x_array_t *array, u32_t index, pt *out_ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  if (index>= array->size) {
    ret = X_ARRAY_BAD_INDEX;
    goto error;
  }

  p = (unsigned char *)(array->eles_data);
  p += (array->ele_size) * index;
  (*out_ele) = p;

error:
  return ret;
}

i32_t 
x_array_push_back_element(x_array_t *array, pt ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  if (!ele) {
    ret = X_ARRAY_ELEMENT_IS_NULL;
    goto error;
  }

  if (array->size >= array->capacity) {
    ret = X_ARRAY_IS_FULL;
    goto error;
  }

  p = (unsigned char *)(array->eles_data);
  p += (array->ele_size) * array->size;
  x_memcpy(p, ele, array->ele_size);
  array->size++;

error:
  return ret;
}

i32_t 
x_array_insert_element_at(x_array_t *array, u32_t index, pt ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array)
  {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  if (!ele) {
    ret = X_ARRAY_ELEMENT_IS_NULL;
    goto error;
  }
  
  if (array->size >= array->capacity) {
    ret = X_ARRAY_IS_FULL;
    goto error;
  }

  if (index > array->size) {
    ret = X_ARRAY_BAD_INDEX;
    goto error;
  }

  p = (unsigned char *)(array->eles_data);
  p += (array->ele_size) * index;

  if (index < array->size) {
    i32_t move_count = array->size - index;
    x_memmove(p + array->ele_size, p, array->ele_size * move_count);
  }

  x_memcpy(p, ele, array->ele_size);
  array->size++;

error:
  return ret;
}

i32_t 
x_array_pop_back_element(x_array_t *array, pt *out_ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  if (!out_ele) {
    ret = X_ARRAY_OUT_ARG_IS_NULL;
    goto error;
  }

  if (array->size <= 0) {
    ret = X_ARRAY_IS_EMPRY;
    goto error;
  }

  p = (unsigned char *)(array->eles_data);
  p += (array->ele_size) * (--array->size);
  (*out_ele) = p;
  
error:
  return ret;
}

i32_t 
x_array_remove_element_at(x_array_t *array, u32_t index, element_destroy_fun *dfun)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  if (array->size <= 0) {
    ret = X_ARRAY_IS_EMPRY;
    goto error;
  }

  if (index >= array->size) {
    ret = X_ARRAY_BAD_INDEX;
    goto error;
  }
  p = (unsigned char *)(array->eles_data);
  p += (array->ele_size) * index;
  if (dfun) {
    (*dfun)(p);
  }

  if (index < array->size-1) {
    i32_t move_count = array->size - 1 - index;
    x_memmove(p, p+ array->ele_size, array->ele_size * move_count);
  }
  
  array->size--;
  
error:
  return ret;
}

i32_t 
x_array_clean(x_array_t *array, element_destroy_fun *dfun)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  i32_t i = 0;

  if (!array) {
    ret = X_ARRAY_IS_NULL;
    goto error;
  }

  p = (unsigned char *)(array->eles_data);
  for (i = 0; i < array->size; ++i) {
    if (dfun) {
      (*dfun)(p);
    }
    p += (array->ele_size);
  }
  
  array->size = 0;
  
error:
  return ret;
}