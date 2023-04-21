#include "base/base_api.h"
#include "gtest/gtest.h"

// #define X_ARRAY_IS_NULL 1
// #define X_ARRAY_MEMORY_ERROR 2
// #define X_ARRAY_ELEMENT_SIZE_IS_ZERO 3
// #define X_ARRAY_CAPACITY_IS_ZREO 4
// #define X_ARRAY_IS_FULL 5
// #define X_ARRAY_IS_EMPRY 6
// #define X_ARRAY_OUT_ARG_IS_NULL 7
// #define X_ARRAY_BAD_INDEX 8
x_array_t *array_null = NULL;
typedef struct arrayElemet
{
  i32_t a;
  i32_t b;
} arrayElemet_t;

TEST(base_array, create_and_destory) {
  x_array_t *array = NULL;
  i32_t ret = X_ARRAY_OK;
  ret = x_array_create(0, 10, &array);
  EXPECT_EQ(ret, X_ARRAY_ELEMENT_SIZE_IS_ZERO);
  EXPECT_EQ(array, array_null);

  ret = x_array_create(sizeof(arrayElemet_t), 0, &array);
  EXPECT_EQ(ret, X_ARRAY_CAPACITY_IS_ZREO);
  EXPECT_EQ(array, array_null);

  ret = x_array_create(sizeof(arrayElemet_t), 10, NULL);
  EXPECT_EQ(ret, X_ARRAY_OUT_ARG_IS_NULL);
  EXPECT_EQ(array, array_null);

  ret = x_array_create(sizeof(arrayElemet_t), 10, &array);
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

  ret = x_array_create(sizeof(arrayElemet_t), 10, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  ret = x_array_get_capacity(NULL, NULL);
  EXPECT_EQ(ret, X_ARRAY_IS_NULL);

  ret = x_array_get_capacity(array, NULL);
  EXPECT_EQ(ret, X_ARRAY_OUT_ARG_IS_NULL);

  ret = x_array_get_capacity(array, &capacity);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_EQ(capacity, 10u);

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

  ret = x_array_create(sizeof(arrayElemet_t), 10, &array);
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
  pt NULLPTR = NULL;
  pt out_eles = NULL;

  ret = x_array_create(sizeof(arrayElemet_t), 10, &array);
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