#include "base/base_api.h"
#include "gtest/gtest.h"


TEST(base_predefine, size) {
  EXPECT_EQ(sizeof(uchar_t), 1);
  EXPECT_EQ(sizeof(i8_t), 1);
  EXPECT_EQ(sizeof(u8_t), 1);

  EXPECT_EQ(sizeof(i16_t), 2);
  EXPECT_EQ(sizeof(u16_t), 2);

  EXPECT_EQ(sizeof(i32_t), 4);
  EXPECT_EQ(sizeof(u32_t), 4);

  EXPECT_EQ(sizeof(i64_t), 8);
  EXPECT_EQ(sizeof(u64_t), 8);

  EXPECT_EQ(sizeof(pt_t), sizeof(pint_t));
}
