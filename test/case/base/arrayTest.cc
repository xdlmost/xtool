#include "base/base_api.h"
#include <stdlib.h>
#include <time.h>
#include "gtest/gtest.h"

x_array_t *array_null = NULL;
#define TEST_ARRAY_ELE_COUNT 1024
#define TEST_ARRAY_ELE_DESTORY_ERROR 1024

typedef struct arrayElemet
{
  i32_t a;
  i32_t b;
} arrayElemet_t;

i32_t 
arrayElemet_destroy_fun(void *mem)
{
  i32_t ret = 0;
  arrayElemet_t **ele_p = (arrayElemet_t **)mem;
  arrayElemet_t *ele = *ele_p;
  if (ele) {
    x_free(ele);
  }
  return ret;
}

i32_t 
arrayElemet_destroy_fail_fun(void *mem)
{
  return TEST_ARRAY_ELE_DESTORY_ERROR;
}

TEST(base_array, create_and_destory) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  ret = x_array_create(0, TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_ELEMENT_SIZE_IS_ZERO);
  EXPECT_EQ(array, array_null);

  ret = x_array_create(sizeof(arrayElemet_t), 0, &array);
  EXPECT_EQ(ret, X_ARRAY_CAPACITY_IS_ZREO);
  EXPECT_EQ(array, array_null);

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, NULL);
  EXPECT_EQ(ret, X_ARRAY_OUT_ARG_IS_NULL);
  EXPECT_EQ(array, array_null);

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  if(array) {
    ret = x_array_destroy(NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, get_capacity) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  u32_t capacity = 0;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  ret = x_array_get_capacity(NULL, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_NULL);

  ret = x_array_get_capacity(array, NULL);
  EXPECT_EQ(ret, X_ARRAY_OUT_ARG_IS_NULL);

  ret = x_array_get_capacity(array, &capacity);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, get_size) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  u32_t size = 0;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  ret = x_array_get_size(NULL, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_NULL);

  ret = x_array_get_size(array, NULL);
  EXPECT_EQ(ret, X_ARRAY_OUT_ARG_IS_NULL);

  ret = x_array_get_size(array, &size);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_EQ(size, 0);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, get_elements) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  pt_t NULLPTR = NULL;
  pt_t out_eles = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  ret = x_array_get_elements(NULL, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_NULL);

  ret = x_array_get_elements(array, NULL);
  EXPECT_EQ(ret, X_ARRAY_OUT_ARG_IS_NULL);

  ret = x_array_get_elements(array, &out_eles);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(out_eles, NULLPTR);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, push_back_element) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_eles = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t ele;
    ele.a = i;
    ele.b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_push_back_element(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_push_back_element(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_push_back_element(array, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  ret = x_array_get_elements(array, &out_eles);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(out_eles, NULLPTR);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    arrayElemet_t *ele_get = (arrayElemet_t *)out_eles;
    ele_get += i;
    EXPECT_EQ(ele_get->a, i);
    EXPECT_EQ(ele_get->b, i*i);
  }

  arrayElemet_t ele;
  ele.a = TEST_ARRAY_ELE_COUNT+1;
  ele.b = (TEST_ARRAY_ELE_COUNT+1) * (TEST_ARRAY_ELE_COUNT+1);

  ret = x_array_push_back_element(array, &ele);
  EXPECT_EQ(ret, X_ARRAY_IS_FULL);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, get_element_at) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_ele = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT/2; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t ele;
    ele.a = i;
    ele.b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_push_back_element(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_push_back_element(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_push_back_element(array, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  ret = x_array_get_element_at(array, TEST_ARRAY_ELE_COUNT, &out_ele);
  EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);
  EXPECT_EQ(out_ele, NULLPTR);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT*100; i++) {
    u32_t index = ((u32_t)rand()%(TEST_ARRAY_ELE_COUNT*2 +100));
    ret = x_array_get_element_at(array, index, &out_ele);
    if(index< TEST_ARRAY_ELE_COUNT/2){
      arrayElemet_t *ele = (arrayElemet_t *)out_ele;
      EXPECT_EQ(ret, X_ARRAY_OK);
      EXPECT_NE(out_ele, NULLPTR);
      EXPECT_EQ(ele->a, index);
      EXPECT_EQ(ele->b, index*index);
    } else {
      EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);
      EXPECT_EQ(out_ele, NULLPTR);
    }
    out_ele = NULL;
  }

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, insert_element_at_0) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_eles = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t ele;
    ele.a = i;
    ele.b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_insert_element_at(NULL, TEST_ARRAY_ELE_COUNT+100, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_insert_element_at(array, TEST_ARRAY_ELE_COUNT+100, &ele);
    EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);

    ret = x_array_insert_element_at(array, 0, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_insert_element_at(array, 0, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  ret = x_array_get_elements(array, &out_eles);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(out_eles, NULLPTR);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    arrayElemet_t *ele_get = (arrayElemet_t *)out_eles;
    ele_get += i;
    EXPECT_EQ(ele_get->a, TEST_ARRAY_ELE_COUNT-i-1);
    EXPECT_EQ(ele_get->b, (TEST_ARRAY_ELE_COUNT-i-1)*(TEST_ARRAY_ELE_COUNT-i-1));
  }

  arrayElemet_t ele;
  ele.a = TEST_ARRAY_ELE_COUNT+1;
  ele.b = (TEST_ARRAY_ELE_COUNT+1) * (TEST_ARRAY_ELE_COUNT+1);

  ret = x_array_insert_element_at(array, 0, &ele);
  EXPECT_EQ(ret, X_ARRAY_IS_FULL);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, insert_element_at_last) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_eles = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t ele;
    ele.a = i;
    ele.b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_insert_element_at(NULL, TEST_ARRAY_ELE_COUNT+100, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_insert_element_at(array, TEST_ARRAY_ELE_COUNT+100, &ele);
    EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);

    ret = x_array_insert_element_at(array, i, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_insert_element_at(array, i, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  ret = x_array_get_elements(array, &out_eles);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(out_eles, NULLPTR);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    arrayElemet_t *ele_get = (arrayElemet_t *)out_eles;
    ele_get += i;
    EXPECT_EQ(ele_get->a, i);
    EXPECT_EQ(ele_get->b, i*i);
  }

  arrayElemet_t ele;
  ele.a = TEST_ARRAY_ELE_COUNT+1;
  ele.b = (TEST_ARRAY_ELE_COUNT+1) * (TEST_ARRAY_ELE_COUNT+1);

  ret = x_array_insert_element_at(array, 0, &ele);
  EXPECT_EQ(ret, X_ARRAY_IS_FULL);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, insert_element_at_random) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_eles = NULL;
  i32_t indexes[TEST_ARRAY_ELE_COUNT];
  x_memzero(indexes, sizeof(i32_t) * TEST_ARRAY_ELE_COUNT);
  srand(time(NULL));
  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    EXPECT_EQ(indexes[i], 0);
  }
  
  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t ele;

    ele.a = i;
    ele.b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_insert_element_at(NULL, TEST_ARRAY_ELE_COUNT+100, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_insert_element_at(array, TEST_ARRAY_ELE_COUNT+100, &ele);
    EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);

    ret = x_array_insert_element_at(array, i, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    do{
      u32_t index = ((u32_t)rand()%(TEST_ARRAY_ELE_COUNT*2 +100));
      ret = x_array_insert_element_at(array, index, &ele);
      if (index <size+1) {
        EXPECT_EQ(ret, X_ARRAY_OK);
      } else {
        EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);
      }

    } while (X_ARRAY_OK != ret);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  ret = x_array_get_elements(array, &out_eles);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(out_eles, NULLPTR);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    arrayElemet_t *ele_get = (arrayElemet_t *)out_eles;
    ele_get += i;
    indexes[ele_get->a] = 1;
  }

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    EXPECT_EQ(indexes[i], 1);
  }

  arrayElemet_t ele;
  ele.a = TEST_ARRAY_ELE_COUNT+1;
  ele.b = (TEST_ARRAY_ELE_COUNT+1) * (TEST_ARRAY_ELE_COUNT+1);

  ret = x_array_insert_element_at(array, 0, &ele);
  EXPECT_EQ(ret, X_ARRAY_IS_FULL);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, pop_back_element) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_ele = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t ele;
    ele.a = i;
    ele.b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_push_back_element(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_push_back_element(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_push_back_element(array, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, TEST_ARRAY_ELE_COUNT-i);

    ret = x_array_pop_back_element(array, &out_ele);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_NE(out_ele, NULLPTR);

    arrayElemet_t *poped_ele = (arrayElemet_t *)out_ele;
    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, TEST_ARRAY_ELE_COUNT-i-1);

    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_NE(out_ele, NULLPTR);
    EXPECT_EQ(poped_ele->a, (TEST_ARRAY_ELE_COUNT-i-1));
    EXPECT_EQ(poped_ele->b, (TEST_ARRAY_ELE_COUNT-i-1)*(TEST_ARRAY_ELE_COUNT-i-1));

    out_ele = NULL;
  }

  ret = x_array_pop_back_element(array, &out_ele);
  EXPECT_EQ(ret, X_ARRAY_IS_EMPRY);
  EXPECT_EQ(out_ele, NULLPTR);

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

// i32_t x_array_remove_element_at(x_array_t *array, u32_t index, element_destroy_fun *dfun);

TEST(base_array, remove_element_at_random) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_ele = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  ret = x_array_remove_element_at(NULL, TEST_ARRAY_ELE_COUNT, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_NULL);

  ret = x_array_remove_element_at(array, TEST_ARRAY_ELE_COUNT, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_EMPRY);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t ele;
    ele.a = i;
    ele.b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_push_back_element(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_push_back_element(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_push_back_element(array, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  for (i = 0; i < TEST_ARRAY_ELE_COUNT*100+100; i++) {
    u32_t size = 0;
    u32_t index = ((u32_t)rand()%(TEST_ARRAY_ELE_COUNT*2 +100));
    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_remove_element_at(array, index, NULL);
    if(size == 0) {
      EXPECT_EQ(ret, X_ARRAY_IS_EMPRY);
    } else {
      if (index<size) {
        u32_t size2 = 0;
        EXPECT_EQ(ret, X_ARRAY_OK);

        ret = x_array_get_size(array, &size2);
        EXPECT_EQ(ret, X_ARRAY_OK);
        EXPECT_EQ(size2, size-1);
      } else {
        EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);
      }
    }
  }
  
  {
    u32_t size = 0;
    ret = x_array_clean(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_clean(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, 0);
  }

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, remove_element_at_random_with_release) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_ele = NULL;

  ret = x_array_create(sizeof(arrayElemet_t*), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  ret = x_array_remove_element_at(NULL, TEST_ARRAY_ELE_COUNT, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_NULL);

  ret = x_array_remove_element_at(array, TEST_ARRAY_ELE_COUNT, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_EMPRY);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t *ele = (arrayElemet_t *)x_calloc(sizeof(arrayElemet_t), 1);
    ele->a = i;
    ele->b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_push_back_element(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_push_back_element(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_push_back_element(array, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  ret = x_array_remove_element_at(array, 0, arrayElemet_destroy_fail_fun);
  EXPECT_EQ(ret, TEST_ARRAY_ELE_DESTORY_ERROR);

  ret = x_array_clean(array, arrayElemet_destroy_fail_fun);
  EXPECT_EQ(ret, TEST_ARRAY_ELE_DESTORY_ERROR);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT*100+100; i++) {
    u32_t size = 0;
    u32_t index = ((u32_t)rand()%(TEST_ARRAY_ELE_COUNT*2 +100));
    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_remove_element_at(array, index, arrayElemet_destroy_fun);
    if(size == 0) {
      EXPECT_EQ(ret, X_ARRAY_IS_EMPRY);
    } else {
      if (index<size) {
        u32_t size2 = 0;
        EXPECT_EQ(ret, X_ARRAY_OK);

        ret = x_array_get_size(array, &size2);
        EXPECT_EQ(ret, X_ARRAY_OK);
        EXPECT_EQ(size2, size-1);
      } else {
        EXPECT_EQ(ret, X_ARRAY_BAD_INDEX);
      }
    }
  }
  
  {
    u32_t size = 0;
    ret = x_array_clean(NULL, arrayElemet_destroy_fun);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_clean(array, arrayElemet_destroy_fun);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, 0);
  }

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

typedef struct iterate_arg
{
  i32_t expect;
  i32_t break_at;
} iterate_arg_t;

i32_t 
x_array_iterate_test(x_array_t *array, pt_t element, pt_t arg)
{
  iterate_arg_t *iarg = (iterate_arg_t *)arg;
  arrayElemet_t *ele = *(arrayElemet_t **)element;
  if (ele->a == iarg->break_at) {
    return X_ARRAY_ITERATE_BREAK;
  }

  if (ele->a == iarg->expect) {
    iarg->expect++;
  }
  return X_ARRAY_OK;
}

TEST(base_array, iter_element) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_ele = NULL;

  ret = x_array_create(sizeof(arrayElemet_t*), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t *ele = (arrayElemet_t *)x_calloc(sizeof(arrayElemet_t), 1);
    ele->a = i;
    ele->b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_push_back_element(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_push_back_element(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_push_back_element(array, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  iterate_arg_t *arg = (iterate_arg_t *)x_malloc(sizeof(iterate_arg_t));
  arg->expect = 0;
  arg->break_at = -1;

  ret = x_array_iterate(array, x_array_iterate_test, arg);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_EQ(arg->expect, TEST_ARRAY_ELE_COUNT);

  {
    u32_t size = 0;
    ret = x_array_clean(NULL, arrayElemet_destroy_fun);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_clean(array, arrayElemet_destroy_fun);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, 0);
  }

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}

TEST(base_array, iter_element_break) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  i32_t i = 0;
  pt_t NULLPTR = NULL;
  pt_t out_ele = NULL;

  ret = x_array_create(sizeof(arrayElemet_t*), TEST_ARRAY_ELE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  for (i = 0; i < TEST_ARRAY_ELE_COUNT; i++) {
    u32_t size = 0;
    u32_t capacity = 0;
    arrayElemet_t *ele = (arrayElemet_t *)x_calloc(sizeof(arrayElemet_t), 1);
    ele->a = i;
    ele->b = i * i;

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i);

    ret = x_array_get_capacity(array, &capacity);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(capacity, TEST_ARRAY_ELE_COUNT);

    ret = x_array_push_back_element(NULL, NULL);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_push_back_element(array, NULL);
    EXPECT_EQ(ret, X_ARRAY_ELEMENT_IS_NULL);

    ret = x_array_push_back_element(array, &ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, i+1);
  }

  iterate_arg_t *arg = (iterate_arg_t *)x_malloc(sizeof(iterate_arg_t));
  arg->expect = 0;
  arg->break_at = TEST_ARRAY_ELE_COUNT/2;

  ret = x_array_iterate(array, x_array_iterate_test, arg);
  EXPECT_EQ(ret, X_ARRAY_ITERATE_BREAK);
  EXPECT_EQ(arg->expect, arg->break_at);

  {
    u32_t size = 0;
    ret = x_array_clean(NULL, arrayElemet_destroy_fun);
    EXPECT_EQ(ret, X_ARRAY_IS_NULL);

    ret = x_array_clean(array, arrayElemet_destroy_fun);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_array_get_size(array, &size);
    EXPECT_EQ(ret, X_ARRAY_OK);
    EXPECT_EQ(size, 0);
  }

  if(array) {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }
}
// i32_t x_array_clean(x_array_t *array, element_destroy_fun *dfun);