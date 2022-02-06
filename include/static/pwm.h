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

#include "errors.h"


pwm_code set_export(bool reserve);
pwm_code set_enable(bool enable);
pwm_code set_duty(uint64_t duty);
pwm_code set_period(uint64_t period);