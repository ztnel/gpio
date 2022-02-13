/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief Example usage of PWM driver
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */
#include <pwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define OPTSTR ":hd:p:"

int shutdown();
void usage();

int shutdown() {
  set_enable(false);
  set_export(false);
  return 0;
}

void usage() {
  printf(
    "Example PWM Driver.\n"
    "Usage:\n"
    "  ex-pwm\n"
    "  ex-pwm -d <ns> -p <ns>\n"
    "  ex-pwm -h | --help\n\n"
    "Options:\n"
    "  -h --help    Show this screen.\n"
    "  -d <ns>      Duty cycle in nanoseconds.\n"
    "  -p <ns>      Period in nanoseconds.\n"
  );
}

int main(int argc, char *argv[]) {
  int c, status, errflg;
  uint64_t duty;
  uint64_t period;
  while ((c = getopt(argc, argv, OPTSTR)) != -1) {
    switch (c) {
      case 'h':
        usage();
        exit(0);
      case 'd':
        duty = atoi(optarg);
        break;
      case 'p' :
        period = atoi(optarg);
        break;
      case ':':
        fprintf(stderr, "-%c without argument\n", optopt);
        errflg++;
        break;
      case '?':
        fprintf(stderr, "unknown argument -%c\n", optopt);
        errflg++;
        break;
      default:
        abort();
    }
  }
  if (errflg) {
    usage();
    exit(2);
  }
  if (!duty || !period) {
    usage();
    exit(0);
  }
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