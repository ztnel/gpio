/**
 * @file test_pwm.cpp
 * @author your name (you@domain.com)
 * @brief unittests for pwm module
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

extern "C" {
  #include <merase.h>
  #include "pwm.h"
}

#include <gtest/gtest.h>
#include <fff.h>

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC3(int, ioctl, const char*, const char*, size_t);
FAKE_VALUE_FUNC2(char*, int64_to_str, uint64_t, size_t*);
FAKE_VOID_FUNC1(free_buffer, char*);
FAKE_VOID_FUNC1(logger_set_level, Level);
FAKE_VOID_FUNC_VARARG(_trace, const char*, ...);
FAKE_VOID_FUNC_VARARG(_error, const char*, ...);
FAKE_VOID_FUNC_VARARG(_warning, const char*, ...);
FAKE_VOID_FUNC_VARARG(_critical, const char*, ...);
FAKE_VOID_FUNC_VARARG(_info, const char*, ...);

class TestPwm : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(ioctl);
      RESET_FAKE(int64_to_str);
      RESET_FAKE(free_buffer);
      RESET_FAKE(logger_set_level)
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
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/export"), 0);
}

TEST_F(TestPwm, SetExportFalse) {
  set_export(false);
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/unexport"), 0);
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
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/pwm0/duty_cycle"), 0);
}

TEST_F(TestPwm, SetPeriodReturn) {
  pwm_code mock_ret = PWM_GENERAL_ERROR;
  ioctl_fake.return_val = mock_ret;
  int result = set_period(1000000);
  ASSERT_EQ(int64_to_str_fake.call_count, 1);
  ASSERT_EQ(result, mock_ret);
}

TEST_F(TestPwm, SetPeriodIoctlArgs) {
  set_period(200000);
  ASSERT_EQ(strcmp(ioctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/pwm0/period"), 0);
}

TEST_F(TestPwm, PwmInit) {
  pwm_init();
  ASSERT_EQ(logger_set_level_fake.call_count, 1);
}
