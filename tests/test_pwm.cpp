
#include <gtest/gtest.h>
#include "fff.h"

extern "C" {
  #include "static/sysfs.h"
  #include "static/pwm.h"
}


DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(pwm_code, ioctl, const char*, const void*, size_t);

class TestPwm : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(ioctl);
      FFF_RESET_HISTORY();
    }
};

TEST_F(TestPwm, IoctlCalled) {
  set_export(true);
  ASSERT_EQ(ioctl_fake.call_count, 1);
}
