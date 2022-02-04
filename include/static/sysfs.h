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

#include <stdio.h>
#include "errors.h"

pwm_code ioctl(const char* path, const void* buf, size_t buf_size);
