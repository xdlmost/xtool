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
  if (ele_size <= 0 || capacity <= 0 || !new_array) {
    ret = X_ARRAY_BAD_ARGUMENT;
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
    ret = X_ARRAY_BAD_ARGUMENT;
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

u32_t 
x_array_get_capacity(x_array_t *array)
{
  return array->capacity;
}

u32_t 
x_array_get_size(x_array_t *array)
{
  return array->size;
}


i32_t 
x_array_get_elements(x_array_t *array, pt_t *out_eles)
{
  i32_t ret = X_ARRAY_OK;
  if (!array || !out_eles) {
    ret = X_ARRAY_BAD_ARGUMENT;
    goto error;
  }

  (*out_eles) = array->eles_data;
error:
  return ret;
}

i32_t 
x_array_get_element_at(x_array_t *array, u32_t index, pt_t *out_ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array || !out_ele) {
    ret = X_ARRAY_BAD_ARGUMENT;
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
x_array_push_back_element(x_array_t *array, pt_t ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;

  if (!array || !ele) {
    ret = X_ARRAY_BAD_ARGUMENT;
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
x_array_insert_element_at(x_array_t *array, u32_t index, pt_t ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array || !ele)
  {
    ret = X_ARRAY_BAD_ARGUMENT;
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
x_array_pop_back_element(x_array_t *array, pt_t *out_ele)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array || !out_ele) {
    ret = X_ARRAY_BAD_ARGUMENT;
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
x_array_remove_element_at(x_array_t *array, u32_t index, element_destroy_fun dfun)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  if (!array) {
    ret = X_ARRAY_BAD_ARGUMENT;
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
    ret = dfun(p);
    if (X_ARRAY_OK != ret) {
      goto error;
    }
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
x_array_clean(x_array_t *array, element_destroy_fun dfun)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  i32_t i = 0;

  if (!array) {
    ret = X_ARRAY_BAD_ARGUMENT;
    goto error;
  }

  p = (unsigned char *)(array->eles_data);
  for (i = 0; i < array->size; ++i) {
    if (dfun) {
      ret = dfun(p);
      if (X_ARRAY_OK != ret) {
        goto error;
      }
    }
    p += (array->ele_size);
  }
  
  array->size = 0;
  
error:
  return ret;
}

i32_t 
x_array_exchange(x_array_t *array, u32_t aindex, u32_t bindex, pt_t exchange_buffer)
{
  i32_t ret = X_ARRAY_OK;

  if (!array || aindex == bindex || aindex >= array->size || bindex >= array->size) {
    ret = X_ARRAY_BAD_ARGUMENT;
    goto error;
  }

  if (exchange_buffer) {
    x_memcpy(exchange_buffer, ((unsigned char *)(array->eles_data)) + aindex * array->ele_size, array->ele_size);
    x_memcpy(((unsigned char *)(array->eles_data)) + aindex * array->ele_size, ((unsigned char *)(array->eles_data)) + bindex * array->ele_size,array->ele_size);
    x_memcpy(((unsigned char *)(array->eles_data)) + bindex * array->ele_size, array->ele_size, exchange_buffer);
  } else {
    unsigned char *buffer = (unsigned char *)x_malloc(array->ele_size);
    x_memcpy(buffer, ((unsigned char *)(array->eles_data)) + aindex * array->ele_size, array->ele_size);
    x_memcpy(((unsigned char *)(array->eles_data)) + aindex * array->ele_size, ((unsigned char *)(array->eles_data)) + bindex * array->ele_size,array->ele_size);
    x_memcpy(((unsigned char *)(array->eles_data)) + bindex * array->ele_size, array->ele_size, buffer);
    x_free(buffer);
  }

error:
  return ret;
}

i32_t 
x_array_iterate(x_array_t *array, x_array_iterate_fun iterate_fun, pt_t arg)
{
  i32_t ret = X_ARRAY_OK;
  unsigned char *p = NULL;
  u32_t index = 0;

  if (!array || !iterate_fun) {
    ret = X_ARRAY_BAD_ARGUMENT;
    goto error;
  }

  if (array->size <= 0) {
    ret = X_ARRAY_IS_EMPRY;
    goto error;
  }

  p = (unsigned char *)(array->eles_data);
  
  while(index < array->size ) {
    if ( X_ARRAY_ITERATE_BREAK == (ret = iterate_fun(array, (pt_t)p, arg))) {
      goto error;
    }
    
    index++;
    p += (array->ele_size);
  }
  
error:
  return ret;
}