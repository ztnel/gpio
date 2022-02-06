#include "include/static/pwm.h"

int main(int argc, char **argv) {
  // set export
  set_export(true);
  // set duty
  set_duty(2000000);
  // set period
  set_period(1000000);
  // set enable
  set_enable(true);
}