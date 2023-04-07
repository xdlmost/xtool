#include "base/x_memory.h"
#include "gtest/gtest.h"

TEST(base_memory, mallc) {
  i32_t i = 10;
  str test_str = NULL;
  str null_str = NULL;
  test_str = (str)x_malloc(i);

  EXPECT_NE(test_str, null_str);
  x_free(test_str);
}

TEST(base_memory, callc) {
  i32_t count = 1000;
  i32_t i;
  i32_t *nums = NULL;
  i32_t *null_nums = NULL;
  nums = (i32_t *)x_calloc(sizeof(i32_t), count);
  EXPECT_NE(nums, null_nums);
  for (i = 0; i < count;++i) {
    EXPECT_EQ(nums[i], 0);
  }
  x_free(nums);
}

TEST(base_memory, reallc) {
  i32_t count = 1000;
  i32_t i;
  i32_t *nums = NULL;
  i32_t *null_nums = NULL;
  nums = (i32_t *)x_realloc(NULL, sizeof(i32_t) * count);
  EXPECT_NE(nums, null_nums);
  x_free(nums);
}

TEST(base_memory, reallc_bigger) {
  i32_t count = 1000;
  i32_t to_count = 2000;
  i32_t i;
  i32_t *nums = NULL;
  i32_t *null_nums = NULL;
  i32_t *nums_to = NULL;
  nums = (i32_t *)x_calloc(sizeof(i32_t), count);
  EXPECT_NE(nums, null_nums);
  for (i = 0; i < count;++i) {
    EXPECT_EQ(nums[i], 0);
    nums[i] = i;
  }

  for (i = 0; i < count;++i) {
    EXPECT_EQ(nums[i], i);
  }

  nums_to = (i32_t *)x_realloc(nums, sizeof(i32_t) * to_count);
  for (i = 0; i < to_count;++i) {
    if(i < count) {
      EXPECT_EQ(nums_to[i], i);
    }
  }
  x_free(nums_to);
}

TEST(base_memory, reallc_smaller) {
  i32_t count = 2000;
  i32_t to_count = 1000;
  i32_t i;
  i32_t *nums = NULL;
  i32_t *null_nums = NULL;
  i32_t *nums_to = NULL;
  nums = (i32_t *)x_calloc(sizeof(i32_t), count);
  EXPECT_NE(nums, null_nums);
  for (i = 0; i < count;++i) {
    EXPECT_EQ(nums[i], 0);
    nums[i] = i;
  }

  for (i = 0; i < count;++i) {
    EXPECT_EQ(nums[i], i);
  }

  nums_to = (i32_t *)x_realloc(nums, sizeof(i32_t) * to_count);
  for (i = 0; i < to_count;++i) {
    if(i < count) {
      EXPECT_EQ(nums_to[i], i);
    }
  }
  x_free(nums_to);
}