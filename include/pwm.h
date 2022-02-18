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

#ifndef PWM_H_
#define PWM_H_

#include <stdbool.h>
#include "errors.h"

enum pwm_polarity {
  NORMAL,
  INVERSE,
};

enum pwm_channel {
  PWM0,
  PWM1,
};

struct pwm_iface {
  uint8_t channel;
  uint64_t duty;
  uint64_t period;
  enum pwm_polarity polarity;
  enum pwm_channel enable;
}; 

void pwm_init();
pwm_status pwm_set_export(bool reserve);
pwm_status pwm_set_enable(bool enable);
pwm_status pwm_set_duty(uint64_t duty);
pwm_status pwm_set_period(uint64_t period);
pwm_status pwm_set_pulse(uint64_t period, uint8_t duty);

#endif  // PWM_H_
