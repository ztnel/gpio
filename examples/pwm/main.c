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
pwm_code set_pulse(uint64_t period, uint8_t duty);

int shutdown() {
  pwm_set_enable(false);
  pwm_set_export(false);
  return 0;
}

void usage() {
  printf(
    "Example PWM Driver.\n"
    "Usage:\n"
    "  ex-pwm\n"
    "  ex-pwm -d <ns> -p <percent>\n"
    "  ex-pwm -h | --help\n\n"
    "Options:\n"
    "  -h --help      Show this screen.\n"
    "  -d <percent>   Positive duty cycle as percentage.\n"
    "  -p <ns>        Period in nanoseconds.\n"
  );
}

/**
 * @brief Set the pwm waveform using a % for positive duty
 * 
 * @param period waveform period in nanoseconds (ie 10,000,000ns -> 10MHz)
 * @param duty positive duty of the waveform as a percentage of the period (ie 50)
 * @return pwm_code 
 */
pwm_code set_pulse(uint64_t period, uint8_t duty) {
  pwm_code status;
  if (duty > 100) {
    return PWM_ARG_ERROR;
  }
  uint64_t _duty = period * (int)duty/100;
  status = set_period(period);
  if (status != 0) {
    return status;
  }
  status = set_duty(_duty);
  if (status != 0) {
    return status;
  }
  return PWM_SUCCESS;
}

int main(int argc, char *argv[]) {
  int c, status, errflg = 0;
  uint64_t duty = 0;
  uint64_t period = 0;
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
  status = pwm_set_export(true);
  if (status != 0) {
    shutdown();
  }
  status = pwm_set_pulse(period, duty);
  if (status != 0) {
    shutdown();
  }
  // set enable
  pwm_set_enable(true);
  if (status != 0) {
    shutdown();
  }
  return 0;
}