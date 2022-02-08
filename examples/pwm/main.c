#include <static/pwm.h>
#include <stdio.h>
#include <stdlib.h>


int shutdown() {
  set_enable(false);
  set_export(false);
  return 0;
}

int main(int argc, char **argv) {
  int status;
  if (argc != 3) {
    // error("Usage: %s duty period", argv[0]);
    return 1;
  }
  printf("Example PWM Driver\n");
  printf("==================\n");
  // read count from argc
  uint64_t duty = atoi(argv[1]);
  uint64_t period = atoi(argv[2]);
  // set export
  status = set_export(true);
  if (status != 0) {
    shutdown();
  }
  // set duty
  status = set_duty(duty);
  if (status != 0) {
    shutdown();
  }
  // set period
  set_period(period);
  if (status != 0) {
    shutdown();
  }
  // set enable
  set_enable(true);
  if (status != 0) {
    shutdown();
  }
  return 0;
}