#include "base/log.h"
#include "base/x_memory.h"
#include "gtest/gtest.h"

TEST(base, log) {
  LOG_ERROR("test error log %s", "hehe");
  LOG_DEBUG("test debug log");
  EXPECT_EQ(0, 0);
}
