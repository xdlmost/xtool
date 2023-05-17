#include "base/base_api.h"
#include "gtest/gtest.h"
#define COMPARE_TEST_TIMES 10000
TEST(base_compare_func, i32_t_compare) {
  i32_t ret = 0;
  i32_t i = 0;
  i32_t v1 = 0;
  i32_t v2 = 0;
  for (i = 0; i < COMPARE_TEST_TIMES; i++) {
    v1 = (i32_t)rand();
    v2 = (i32_t)rand();
    if (v1 > v2) {
      EXPECT_EQ(1, x_compare_func_i32(v1, v2));
      EXPECT_EQ(1, x_compare_func_i32_ptr(&v1, &v2, NULL));
    } else if (v1 < v2) {
      EXPECT_EQ(-1, x_compare_func_i32(v1, v2));
      EXPECT_EQ(-1, x_compare_func_i32_ptr(&v1, &v2, NULL));
    } else{
      EXPECT_EQ(0, x_compare_func_i32(v1, v2));
      EXPECT_EQ(0, x_compare_func_i32_ptr(&v1, &v2, NULL));
    }
  }
}