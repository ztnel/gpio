/**
 * @file clock.h
 * @author ztnel (christian.sargusingh@gbatteries.com)
 * @brief 
 * @version 0.1
 * @date 2022-04
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

#include "mem.h"

/**
 * @brief GPIO Clock manager control and status bits
 * 5.4. General Purpose GPIO Clocks (Table 98. General Purpose Clocks Registers)
 */
#define CLK_BASE                (MEM_BCM2711_BASE + 0x00101000)

/**
 * @brief The clock manager mem space for the BCM2711 is undocumented however
 * the mappings seem to be the same as the BCM2835:
 * https://elinux.org/BCM2835_registers#CM
 */
#define CLK_LEN                 0xA8
#define CLK_PCM                 0x98
#define CLK_PWM                 0xA0

#define CM_PASSWD               (0x5A << 24)
#define CLK_CTL_KILL            (CM_PASSWD | (1 << 5))
#define CLK_CTL_BUSY            (CM_PASSWD | (1 << 7))
#define CLK_CTL_EN(x)           (CM_PASSWD | ((x) << 4))
#define CLK_DIV_DIVI(x)         (CM_PASSWD | ((x) << 12))
#define CLK_SRC(x)              (CM_PASSWD | ((x) << 0))

// clock sources
#define CLK_GND                 (uint8_t) 0
#define CLK_OSC                 (uint8_t) 1
#define CLK_DEBUG0              (uint8_t) 2
#define CLK_DEBUG1              (uint8_t) 3
#define CLK_PLLA                (uint8_t) 4
#define CLK_PLLC                (uint8_t) 5
#define CLK_PLLD                (uint8_t) 6
#define CLK_HDMI                (uint8_t) 7

#define CLK_MICROS              1

typedef struct clk_t {
  uint32_t cs;          // control register
  uint32_t div;         // divisor register
} clk_t;

void clk_init(uint8_t divisor);
void clk_reset();

#endif  // CLOCK_H_
