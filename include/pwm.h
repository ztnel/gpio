/**
 * @file pwm.h
 * @author ztnel (christian.sargusingh@gbatteries.com)
 * @brief 
 * @version 0.1
 * @date 2022-01
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include "mem.h"
#include "errors.h"

#define PWM0_BASE        (MEM_BCM2711_BASE + 0x0020c000)
#define PWM1_BASE        (MEM_BCM2711_BASE + 0x0020c800)

// control register bits
#define PWM_MSEN2(x)      ((x) << 15)       // channel 2 M/S ratio enable
#define PWM_USEF2(x)      ((x) << 13)       // channel 2 use fifo
#define PWM_POLA2(x)      ((x) << 12)       // channel 2 polarity
#define PWM_SBIT2(x)      ((x) << 11)       // channel 2 silence bit
#define PWM_RPTL2(x)      ((x) << 10)       // channel 2 repeat last data
#define PWM_MODE2(x)      ((x) << 9)        // channel 2 mode
#define PWM_PWMEN2(x)     ((x) << 8)        // channel 2 enable
#define PWM_MSEN1(x)      ((x) << 7)        // channel 1 M/S ratio enable
#define PWM_CLRF(x)       ((x) << 6)        // clear fifo
#define PWM_USEF1(x)      ((x) << 5)        // channel 1 use fifo
#define PWM_POLA1(x)      ((x) << 4)        // channel 1 polarity
#define PWM_SBIT1(x)      ((x) << 3)        // channel 1 silence bit
#define PWM_RPTL1(x)      ((x) << 2)        // channel 1 repeat last data
#define PWM_MODE1(x)      ((x) << 1)        // channel 1 mode
#define PWM_PWMEN1(x)     ((x) << 0)        // channel 1 enable

// status register bits
#define PWM_STA2(x)       ((x) << 10)       // channel 2 state
#define PWM_STA1(x)       ((x) << 9)        // channel 1 state
#define PWM_BERR(x)       ((x) << 8)        // bus error flag
#define PWM_GAP02(x)      ((x) << 5)        // channel 2 gap occurred flag
#define PWM_GAP01(x)      ((x) << 4)        // channel 2 gap occurred flag
#define PWM_RERR1(x)      ((x) << 3)        // fifo read error flag
#define PWM_WERR1(x)      ((x) << 2)        // fifo write error flag
#define PWM_EMPT1(x)      ((x) << 1)        // fifo empty flag
#define PWM_FULL1(x)      ((x) << 0)        // fifo full flag

typedef struct pwm_t {
  uint32_t ctl;       // control register
  uint32_t sta;       // status register
  uint32_t dmac;      // dma configuration
  uint32_t pd1[2];    // padding
  uint32_t rng1;      // pwm channel 1 range
  uint32_t dat1;      // pwm channel 1 data
  uint32_t fif1;      // pwm fifo input
  uint32_t pd2[2];    // padding
  uint32_t rng2;      // pwm channel 2 range
  uint32_t dat2;      // pwm channel 2 data
} pwm_t;

#endif  // PWM_H_
