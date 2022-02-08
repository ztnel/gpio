/**
 * @file pwm.c
 * @author your name (you@domain.com)
 * @brief linux pwm driver 
 * @version 0.1
 * @date 2022-01
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "static/errors.h"
#include "static/pwm.h"
#include "static/sysfs.h"


/**
 * @brief Reserve or close access to pwmchip0
 * 
 * @param reserve reservation flag 
 * @return pwm_code 
 */
pwm_code set_export(bool reserve) {
  pwm_code status;
  size_t size = sizeof(uint8_t);
  if (reserve) {
    status = ioctl(EXPORT_PATH, "1", size);
  } else {
    status = ioctl(UNEXPORT_PATH, "1", size);
  }
  return status;
}

/**
 * @brief Enable/Disable pwm channel
 * 
 * @param enable flag for enable/disable
 * @return pwm_code 
 */
pwm_code set_enable(bool enable) {
  pwm_code status;
  size_t size = sizeof(uint8_t);
  if (enable) {
    status = ioctl(ENABLE_PATH, "1", size);
  } else {
    status = ioctl(ENABLE_PATH, "0", size);
  }
  return status;
}

/**
 * @brief Set the duty cycle of the pwm waveform in ns
 * 
 * @param duty positive pulse width in ns
 * @return pwm_code 
 */
pwm_code set_duty(uint64_t duty) {
  size_t size;
  char *buf = int64_to_str(duty, &size);
  printf("Buffer: %s Size: %d\n", buf, size);
  pwm_code status = ioctl(DUTY_PATH, buf, size);
  free_buffer(buf);
  return status;
}

/**
 * @brief Set the waveform pulse period in ns 
 * 
 * @param period pulse period in ns
 * @return pwm_code 
 */
pwm_code set_period(uint64_t period) {
  char buf[sizeof(uint64_t)];
  sprintf(buf, "%ld", period);
  return ioctl(PERIOD_PATH, buf, sizeof(uint64_t));
}
