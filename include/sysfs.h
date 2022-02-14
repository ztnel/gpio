/**
 * @file sysfs.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#ifndef SYSFS_H_
#define SYSFS_H_

#include <stdint.h>
#include <stdio.h>
#include "errors.h"

// constant path definitions
static const char EXPORT_PATH[] = "/sys/class/pwm/pwmchip0/export";
static const char UNEXPORT_PATH[] = "/sys/class/pwm/pwmchip0/unexport";
static const char PERIOD_PATH[] = "/sys/class/pwm/pwmchip0/pwm0/period";
static const char DUTY_PATH[] = "/sys/class/pwm/pwmchip0/pwm0/duty_cycle";
static const char ENABLE_PATH[] = "/sys/class/pwm/pwmchip0/pwm0/enable";


int ioctl(const char* path, const char* buf, size_t buf_size);
char* int64_to_str(uint64_t value, size_t *size);
void free_buffer(char* buf);

#endif  // SYSFS_H_
