
#ifndef PWM_ERRORS_H_
#define PWM_ERRORS_H_

#include <stdint.h>

typedef int pwm_code;

#define PWM_SUCCESS                 (uint8_t) 0
#define PWM_GENERAL_ERROR           (uint8_t) 1
#define PWM_SYSFS_WRITE_ERROR       (uint8_t) 2
#define PWM_SYSFS_CLOSE_ERROR       (uint8_t) 3
#define PWM_ARG_ERROR               (uint8_t) 4

#endif // PWM_ERRORS_H_