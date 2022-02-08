
#include <gtest/gtest.h>
#include <fff.h>

extern "C" {
  #include "static/sysfs.h"
  #include "static/pwm.h"
}


DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(pwm_code, ioctl, const char*, const char*, size_t);
FAKE_VALUE_FUNC(char*, int64_to_str, uint64_t, size_t*);
FAKE_VOID_FUNC(free_buffer, char*);

class TestPwm : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(ioctl);
      RESET_FAKE(int64_to_str);
      RESET_FAKE(free_buffer);
      FFF_RESET_HISTORY();
    }
};

TEST_F(TestPwm, SetExportReturn) {
  pwm_code mock_ret = PWM_GENERAL_ERROR;
  ioctl_fake.return_val = mock_ret;
  int result = set_export(true);
  ASSERT_EQ(result, mock_ret);
  ASSERT_EQ(ioctl_fake.call_count, 1);
}

TEST_F(TestPwm, SetExportTrue) {
  set_export(true);
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, EXPORT_PATH), 0);
}

TEST_F(TestPwm, SetExportFalse) {
  set_export(false);
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, UNEXPORT_PATH), 0);
}

TEST_F(TestPwm, SetEnableReturn) {
  pwm_code mock_ret = PWM_GENERAL_ERROR;
  ioctl_fake.return_val = mock_ret;
  int result = set_enable(true);
  ASSERT_EQ(result, mock_ret);
}

TEST_F(TestPwm, SetEnableTrue) {
  set_enable(true);
  ASSERT_EQ(strcmp(ioctl_fake.arg1_val, "1"), 0);
}

TEST_F(TestPwm, SetEnableFalse) {
  set_enable(false);
  ASSERT_EQ(strcmp(ioctl_fake.arg1_val, "0"), 0);
}

TEST_F(TestPwm, SetDutyReturn) {
  pwm_code mock_ret = PWM_GENERAL_ERROR;
  ioctl_fake.return_val = mock_ret;
  int result = set_duty(1000000);
  ASSERT_EQ(result, mock_ret);
}

TEST_F(TestPwm, SetDutyIoctlArgs) {
  set_duty(200000);
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, DUTY_PATH), 0);
}

TEST_F(TestPwm, SetPeriodReturn) {
  pwm_code mock_ret = PWM_GENERAL_ERROR;
  ioctl_fake.return_val = mock_ret;
  int result = set_period(1000000);
  ASSERT_EQ(result, mock_ret);
}
TEST_F(TestPwm, SetPeriodIoctlArgs) {
  set_period(200000);
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, PERIOD_PATH), 0);
}