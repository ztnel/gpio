#include <gtest/gtest.h>
#include "mocks/pwm_mock.h"

extern "C" {
#include "static/pwm.h"
}


using ::testing::_;

namespace {
  class TestPwm : public TestFixture {
    public:
      TestPwm() {};
  };

  TEST_F(TestPwm, ExportReturnsSuccess) {
    EXPECT_CALL(*mock_pwm, ioctl(_,_,_));
    set_export(true);
  }
} //namespace
