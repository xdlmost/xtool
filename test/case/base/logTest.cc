#include "base/base_api.h"
#include "gtest/gtest.h"

TEST(base_log, print) {
  LOG_ERROR("test error log %s", "hehe");
  LOG_DEBUG("test debug log");
  EXPECT_EQ(0, 0);
}
