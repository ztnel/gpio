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
#include <string.h>
#include <merase.h>
#include "errors.h"
#include "pwm.h"
#include "sysfs.h"


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
    trace("pwm export returned status: %d", status);
  } else {
    status = ioctl(UNEXPORT_PATH, "1", size);
    trace("pwm unexport returned status: %d", status);
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
    trace("Set pwm enable returned status: %d", status);
  } else {
    status = ioctl(ENABLE_PATH, "0", size);
    trace("Set pwm disable returned status: %d", status);
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
  info("Buffer: %s Size: %d\n", buf, size);
  pwm_code status = ioctl(DUTY_PATH, buf, size);
  free_buffer(buf);
  trace("Set pwm duty returned status: %d", status);
  return status;
}

/**
 * @brief Set the waveform pulse period in ns 
 * 
 * @param period pulse period in nanoseconds
 * @return pwm_code 
 */
pwm_code set_period(uint64_t period) {
  size_t size;
  char *buf = int64_to_str(period, &size);
  info("Buffer: %s Size: %d\n", buf, size);
  pwm_code status = ioctl(PERIOD_PATH, buf, size);
  free_buffer(buf);
  trace("Set pwm period returned status: %d", status);
  return status;
}

/**
 * @brief Set the pwm waveform using a % for positive duty
 * 
 * @param period waveform period in nanoseconds (ie 10,000,000ns -> 10MHz)
 * @param duty positive duty of the waveform as a percentage of the period (ie 50)
 * @return pwm_code 
 */
pwm_code set_pulse(uint64_t period, uint8_t duty) {
  pwm_code status;
  if (duty > 100) {
    error("Invalid argument for duty: %i", duty);
    return PWM_ARG_ERROR;
  }
  uint64_t _duty = period * (int)duty/100;
  trace("Computed duty: %lld", _duty);
  status = set_period(period);
  if (status != 0) {
    error("Error occurred while setting PWM period with %lld", period);
    return status;
  }
  status = set_duty(_duty);
  if (status != 0) {
    error("Error occurred while setting PWM duty with: %lld", _duty);
    return status;
  }
  return PWM_SUCCESS;
}


/**
 * @brief Initialize the pwm api
 * 
 */
void pwm_init() {
  logger_set_level(TRACE);
}