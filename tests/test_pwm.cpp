#include <gtest/gtest.h>
#include "mocks/pwm_mock.h"

extern "C" {
#include "static/pwm.h"
}

namespace {
  class TestPwm {
    protected:
      void SetUp() {};
      void TearDown() {};
  };
  using ::testing::_;
  TEST(TestPwm, ExportReturnsSuccess) {
    MockPwm mock_pwm;
    EXPECT_CALL(mock_pwm, ioctl(_,_,_));
    ASSERT_EQ(set_export(true), 0);
  }
} //namespace
