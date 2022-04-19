/**
 * @file pwm.c
 * @author ztnel (christian.sargusingh@gbatteries.com)
 * @brief BCM2711 linux pwm driver
 * @version 0.1
 * @date 2022-01
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <merase.h>

#include "pwm.h"


/**
 * @brief Initialize the pwm interface and populate parameters
 * 
 */
pwm_err_t pwm_init() {
  info("pwm state initialized");
  return ;
}

