#include "gtest/gtest.h"

extern "C" {
#include "static/pwm.h"
}

TEST(TestPwm, TestHello) {
  ASSERT_EQ(1, 1);
}