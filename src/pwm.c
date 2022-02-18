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
#include <pthread.h>
#include "errors.h"
#include "pwm.h"
#include "sysfs.h"


// constant path definitions
static const char _EXPORT_PATH[] = "/sys/class/pwm/pwmchip0/export";
static const char _UNEXPORT_PATH[] = "/sys/class/pwm/pwmchip0/unexport";
static const char _PERIOD_PATH[] = "/sys/class/pwm/pwmchip0/pwm0/period";
static const char _DUTY_PATH[] = "/sys/class/pwm/pwmchip0/pwm0/duty_cycle";
static const char _ENABLE_PATH[] = "/sys/class/pwm/pwmchip0/pwm0/enable";
static const char _POLARITY_PATH[] = "/sys/class/pwm/pwmchip0/pwm0/polarity";

static struct pwm_iface pwm = {
  .channel=PWM0,
  .duty=0,
  .period=0,
  .polarity=NORMAL,
  .enable=false
};

static void _initialize_state();

/**
 * @brief Initialize the pwm interface and populate parameters
 * 
 */
void pwm_init() {
  pwm_set_export(true);
  _initialize_state();
  info("pwm state initialized");
}

/**
 * @brief Read pwm state variables and populate local struct
 * 
 */
static void _initialize_state() {
  char *buf;

  buf = rctl(_DUTY_PATH, 8);
  if (buf != NULL)
    pwm.duty = atoll(buf);
    free_buffer(buf);

  buf = rctl(_PERIOD_PATH, 8);
  if (buf != NULL)
    pwm.period = atoll(buf);
    free_buffer(buf);

  buf = rctl(_ENABLE_PATH, 5);
  if (buf != NULL)
    pwm.enable = (strcmp(buf, "1") == 0) ? true : false;
    free_buffer(buf);

  buf = rctl(_POLARITY_PATH, 7);
  if (buf != NULL)
    pwm.polarity = (strcmp(buf, "normal") == 0) ? NORMAL : INVERSE;
    free_buffer(buf);
}

/**
 * @brief Reserve or close access to pwmchip0
 * 
 * @param reserve reservation flag 
 * @return pwm_status 
 */
pwm_status pwm_set_export(bool reserve) {
  pwm_status status;
  size_t size = sizeof(uint8_t);
  if (reserve) {
    status = wctl(_EXPORT_PATH, "1", size);
    trace("pwm export returned status: %d", status);
  } else {
    status = wctl(_UNEXPORT_PATH, "1", size);
    trace("pwm unexport returned status: %d", status);
  }
  return status;
}

/**
 * @brief Enable/Disable pwm channel
 * 
 * @param enable flag for enable/disable
 * @return pwm_status 
 */
pwm_status pwm_set_enable(bool enable) {
  pwm_status status;
  size_t size = sizeof(uint8_t);
  if (enable) {
    status = wctl(_ENABLE_PATH, "1", size);
    trace("Set pwm enable returned status: %d", status);
  } else {
    status = wctl(_ENABLE_PATH, "0", size);
    trace("Set pwm disable returned status: %d", status);
  }
  return status;
}

/**
 * @brief Set the duty cycle of the pwm waveform in ns
 * 
 * @param duty positive pulse width in ns
 * @return pwm_status 
 */
pwm_status pwm_set_duty(uint64_t duty) {
  size_t size;
  char *buf = int64_to_str(duty, &size);
  info("Buffer: %s Size: %d\n", buf, size);
  pwm_status status = wctl(_DUTY_PATH, buf, size);
  free_buffer(buf);
  trace("Set pwm duty returned status: %d", status);
  return status;
}

/**
 * @brief Set the waveform pulse period in ns 
 * 
 * @param period pulse period in nanoseconds
 * @return pwm_status 
 */
pwm_status pwm_set_period(uint64_t period) {
  size_t size;
  char *buf = int64_to_str(period, &size);
  info("Buffer: %s Size: %d\n", buf, size);
  pwm_status status = wctl(_PERIOD_PATH, buf, size);
  free_buffer(buf);
  trace("Set pwm period returned status: %d", status);
  return status;
}
