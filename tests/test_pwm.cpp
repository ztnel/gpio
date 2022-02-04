#include <gtest/gtest.h>
#include <fff.h>

extern "C" {
#include "static/pwm.h"
}

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC3(pwm_code, ioctl, const char*, const void*, size_t);


TEST(TestPwm, ExportReturnsSuccess) {
  set_export(true);
  // ASSERT_EQ(ioctl.call_count, 1);
}
