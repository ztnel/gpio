/**
 * @file pwm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#include <stdio.h>
#include "errors.h"

// constant path definitions
static const char EXPORT[] = "/sys/class/pwm/pwmchip0/export";
static const char UNEXPORT[] = "/sys/class/pwm/pwmchip0/unexport";
static const char PERIOD[] = "/sys/class/pwm/pwmchip0/pwm0/period";
static const char DUTY[] = "/sys/class/pwm/pwmchip0/pwm0/duty_cycle";
static const char ENABLE[] = "/sys/class/pwm/pwmchip0/pwm0/enable";

static FILE *exec(char *cmd);
static pwm_code ioctl(const char* path, const void* buf, size_t buf_size);

pwm_code get_status();
pwm_code set_export(bool reserve);
pwm_code set_enable(bool enable);
pwm_code set_duty(uint64_t duty);
pwm_code set_period(uint64_t period);