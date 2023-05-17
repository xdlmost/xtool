#include "base/base_api.h"
#include "gtest/gtest.h"
#define TEST_RBTREE_COUNT 10240

TEST(base_rbtree, create) {
  i32_t ret = 0;
  x_rbtree_t *rbt = NULL;
  ret = x_rbtree_create(NULL);
  EXPECT_EQ(ret, X_RETREE_OUT_ARG_IS_NULL);

  ret = x_rbtree_create(&rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  if (rbt) {
    x_rbtree_destroy(rbt);
  }
}

TEST(base_rbtree, check_empty) {
  i32_t ret = 0;
  x_rbtree_t *rbt = NULL;

  ret = x_rbtree_create(&rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  if (rbt) {
    x_rbtree_destroy(rbt);
  }
}

TEST(base_rbtree, insert_0) {
  i32_t ret = 0;
  x_rbtree_t *rbt = NULL;

  ret = x_rbtree_create(&rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 0);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  if (rbt) {
    x_rbtree_destroy(rbt);
  }
}

TEST(base_rbtree, insert_0_0) {
  i32_t ret = 0;
  x_rbtree_t *rbt = NULL;

  ret = x_rbtree_create(&rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 0);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 0);
  EXPECT_EQ(ret, X_RETREE_KEY_DUPLICATED);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);
  if (rbt) {
    x_rbtree_destroy(rbt);
  }
}

TEST(base_rbtree, insert_0_1) {
  i32_t ret = 0;
  x_rbtree_t *rbt = NULL;

  ret = x_rbtree_create(&rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 0);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 1);
  EXPECT_EQ(ret, X_RETREE_OK);
  if (rbt) {
    x_rbtree_destroy(rbt);
  }
}

TEST(base_rbtree, insert_0_1_2) {
  i32_t ret = 0;
  x_rbtree_t *rbt = NULL;

  ret = x_rbtree_create(&rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 0);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 1);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_insert(rbt, 2);
  EXPECT_EQ(ret, X_RETREE_OK);

  ret = x_rbtree_check(rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  if (rbt) {
    x_rbtree_destroy(rbt);
  }
}

#define GT_LEVLES_COUNT   30
struct rbtree_iterate_test_arg
{
  i32_t last;
  i32_t iterated_count;
  i32_t levels[GT_LEVLES_COUNT];
};

i32_t 
__gt_x_rbtree_iterate_test(x_rbtree_t *rbtree, i32_t index, i32_t level, i32_t data, pt_t arg)
{
  struct rbtree_iterate_test_arg *rbarg = (struct rbtree_iterate_test_arg *)arg;
  EXPECT_EQ(rbarg->last+1, data);
  rbarg->last = data;

  EXPECT_EQ(rbarg->iterated_count, index);
  rbarg->iterated_count++;
  rbarg->levels[level]++;
  return 0;
}

TEST(base_rbtree, insert_random) {
  i32_t ret = 0;
  x_rbtree_t *rbt = NULL;
  x_array_t *array = NULL;
  x_array_t *array_null = NULL;
  i32_t i = 0;

  ret = x_array_create(sizeof(i32_t), TEST_RBTREE_COUNT, &array);
  EXPECT_EQ(ret, X_ARRAY_OK);
  EXPECT_NE(array, array_null);

  ret = x_rbtree_create(&rbt);
  EXPECT_EQ(ret, X_RETREE_OK);

  for (i = 0; i < TEST_RBTREE_COUNT;i++) {
    ret = x_array_push_back_element(array, &i);
    EXPECT_EQ(ret, X_ARRAY_OK);
  }

  for (i = 0; i < TEST_RBTREE_COUNT;i++) {
    u32_t index = ((u32_t)rand()%(TEST_RBTREE_COUNT-i));
    i32_t *out_ele = NULL;
    ret = x_array_get_element_at(array, index, (void**)&out_ele);
    EXPECT_EQ(ret, X_ARRAY_OK);

    ret = x_rbtree_insert(rbt, *out_ele);
    EXPECT_EQ(ret, X_RETREE_OK);

    ret = x_rbtree_check(rbt);
    EXPECT_EQ(ret, X_RETREE_OK);

    ret = x_array_remove_element_at(array, index, NULL);
    EXPECT_EQ(ret, X_ARRAY_OK);
  }

  struct rbtree_iterate_test_arg rbarg;
  x_memzero(&rbarg, sizeof(struct rbtree_iterate_test_arg));
  rbarg.last = -1;

  ret = x_rbtree_inorder_iterate(rbt, __gt_x_rbtree_iterate_test, &rbarg);
  for (i = 0; i < GT_LEVLES_COUNT; ++i) {
    LOG_DEBUG("Level[%d]:%d", i, rbarg.levels[i]);
  }
  LOG_DEBUG("height:%d", x_rbtree_get_height(rbt));

  if (array)
  {
    ret = x_array_destroy(array);
    EXPECT_EQ(ret, X_ARRAY_OK);
    array = NULL;
  }

  if (rbt) {
    x_rbtree_destroy(rbt);
  }
}