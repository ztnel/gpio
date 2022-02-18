
#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdint.h>

typedef int pwm_status;

#define PWM_SUCCESS                 (uint8_t) 0
#define PWM_GENERAL_ERROR           (uint8_t) 1
#define PWM_SYSFS_WRITE_ERROR       (uint8_t) 2
#define PWM_SYSFS_READ_ERROR        (uint8_t) 3
#define PWM_SYSFS_CLOSE_ERROR       (uint8_t) 4
#define PWM_ARG_ERROR               (uint8_t) 5

#endif  // ERRORS_H_
