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

#include <fff.h>
#include <gtest/gtest.h>

extern "C" {
  #include <merase.h>
  #include "pwm.h"
  #include "sysfs.h"
}

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC2(char *, rctl, const char *, int);
FAKE_VALUE_FUNC3(int, wctl, const char *, const char *, size_t);
FAKE_VALUE_FUNC2(char *, int64_to_str, uint64_t, size_t *);
FAKE_VOID_FUNC1(free_buffer, char*);
FAKE_VOID_FUNC_VARARG(merase_log, enum Level, const char *, int, const char *, ...);

#define FFF_FAKES_LIST(FAKE)  \
  FAKE(wctl)                  \
  FAKE(rctl)                  \
  FAKE(int64_to_str)          \
  FAKE(free_buffer)           \
  FAKE(merase_log)

namespace {
class TestPwm : public testing::Test {
  protected:
    void SetUp() override {
      FFF_FAKES_LIST(RESET_FAKE);
      FFF_RESET_HISTORY();
    }
};

TEST_F(TestPwm, set_export_true) {
  wctl_fake.return_val = PWM_SUCCESS;
  pwm_status status = pwm_set_export(true);
  ASSERT_EQ(strcmp(wctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/export"), 0);
  ASSERT_EQ(status, PWM_SUCCESS);
}

TEST_F(TestPwm, set_export_false) {
  wctl_fake.return_val = PWM_GENERAL_ERROR;
  pwm_status status = pwm_set_export(false);
  ASSERT_EQ(strcmp(wctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/unexport"), 0);
  ASSERT_EQ(status, PWM_GENERAL_ERROR);
}

TEST_F(TestPwm, set_enable_true) {
  wctl_fake.return_val = PWM_SUCCESS;
  pwm_status status = pwm_set_enable(true);
  ASSERT_EQ(strcmp(wctl_fake.arg1_val, "1"), 0);
  ASSERT_EQ(status, PWM_SUCCESS);
}

TEST_F(TestPwm, set_enable_false) {
  wctl_fake.return_val = PWM_GENERAL_ERROR;
  pwm_status status = pwm_set_enable(false);
  ASSERT_EQ(strcmp(wctl_fake.arg1_val, "0"), 0);
  ASSERT_EQ(status, PWM_GENERAL_ERROR);
}

TEST_F(TestPwm, set_duty) {
  wctl_fake.return_val = PWM_SUCCESS;
  pwm_status status = pwm_set_duty(200000);
  ASSERT_EQ(strcmp(wctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/pwm0/duty_cycle"), 0);
  ASSERT_EQ(status, PWM_SUCCESS);
}

TEST_F(TestPwm, set_period) {
  wctl_fake.return_val = PWM_SUCCESS;
  pwm_status status = pwm_set_period(1000000);
  ASSERT_EQ(strcmp(wctl_fake.arg0_val, "/sys/class/pwm/pwmchip0/pwm0/period"), 0);
  ASSERT_EQ(int64_to_str_fake.call_count, 1);
  ASSERT_EQ(status, PWM_SUCCESS);
}

TEST_F(TestPwm, pwm_init) {
  pwm_init();
  ASSERT_EQ(wctl_fake.call_count, 1);
  ASSERT_EQ(rctl_fake.call_count, 4);
}
}