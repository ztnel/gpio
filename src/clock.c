

#include <unistd.h>

#include "merase.h"
#include "clock.h"

static volatile clk_t *clk_reg;

/**
 * @brief 
 * 
 * @param src clock source code (see header definitions)
 * @param divisor clock divisor
 */
void clk_init(uint8_t src, uint16_t divisor) {
  // truncate to 1 byte
  src &= 0xF;
  // truncate to 3 bytes
  divisor &= 0xFFF;
  // map peripherals to virtual memory space
  uint8_t *cm_base_ptr = map_mem(CLK_BASE, CLK_LEN);
  clk_reg = (clk_t *)(cm_base_ptr + CLK_PCM);
  // kill the clock if busy
  if (clk_reg->cs & CLK_CTL_BUSY) {
    do {
      clk_reg->cs = CLK_CTL_KILL;
    } while (clk_reg->cs & CLK_CTL_BUSY);
  }
  clk_reg->cs = CLK_SRC(src);
  usleep(10);
  clk_reg->div = CLK_DIV_DIVI(divisor);
}

void clk_enable() {
  // Enable the clock
  clk_reg->cs |= CLK_CTL_EN(1);
  info("Clock enabled");
}

void clk_reset() {
  clk_reg->cs |= CLK_CTL_EN(0);
  // kill the clock if busy
  if (clk_reg->cs & CLK_CTL_BUSY) {
    do {
      clk_reg->cs = CLK_CTL_KILL;
    } while (clk_reg->cs & CLK_CTL_BUSY);
  }
  info("Clock reset success");
}

