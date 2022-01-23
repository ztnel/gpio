/**
 * @file pwm.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "pwm/pwm.h"

FILE *exec(char *cmd) {
  // execute kernel command
  FILE *fp = popen(cmd, "r");
  if (fp == NULL) {
    printf("Failed to run command %s\n\r", cmd);
    exit(1);
  }
  return fp;
}

void get_pwm_status() {
  FILE *fd = exec("sudo dtparam -l");
  char output[1024];
  int tx_found = 0;
  int status;
  char indicator[] = "pwm-2chan";
  char command[] = "sudo dtoverlay pwm-2chan";
  while (fgets(output, sizeof(output), fd != NULL)) {
    printf("%s\n\r", output);
    fflush(stdout);
    if (strstr(output, indicator) != NULL) {
      tx_found = 1;
    }
  }
  if (tx_found == 0) {
    fd = exec(command);
    sleep(2);
  }
  status = pclose(fd);
  if (status == -1) {
    printf("Error when closing process %s\n\r", fd);
  }
}

int main(int argc, char **argv) {
  int status;
  get_pwm_status();
  // open pwm export for write only
  int fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
  // write a single byte to fd
  write(fd, "0", 1);
  status = close(fd);
  if (status == -1) {
    printf("Error when closing file: %s\n\r", fd);
  }
  // set PWM period
  fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
  write(fd, 10000000, 8);
  status = close(fd);
  if (status == -1) {
    printf("Error when closing file: %s\n\r", fd);
  }
  // set PWM duty
  fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
  write(fd, 1000000, 7);
  status = close(fd);
  if (status == -1) {
    printf("Error when closing file: %s\n\r", fd);
  }
  // set PWM enable
  fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
  write(fd, 1, 1);
  status = close(fd);
  if (status == -1) {
    printf("Error when closing file: %s\n\r", fd);
  }


}