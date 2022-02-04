/**
 * @file pwm.c
 * @author your name (you@domain.com)
 * @brief linux pwm driver 
 * @version 0.1
 * @date 2022-01
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "static/errors.h"
#include "static/pwm.h"


/**
 * @brief Execute kernel command
 * 
 * @param cmd command as a string buffer
 * @return FILE* 
 */
static FILE *exec(char *cmd) {
  // execute kernel command
  FILE *fp = popen(cmd, "r");
  if (fp == NULL) {
    printf("Failed to run command %s\n\r", cmd);
    pclose(fp);
    exit(1);
  }
  return fp;
}

/**
 * @brief Write data to sysfs
 * 
 * @param path sysfs path
 * @param buf data buffer
 * @param buf_size data buffer size in bytes
 * @return pwm_code 
 */
static pwm_code ioctl(const char* path, const void* buf, size_t buf_size) {
  if (path == NULL || buf == NULL || buf_size == 0) {
    printf("Invalid arg");
    return PWM_ARG_ERROR;
  }
  printf("Opening path %s for write of %x with size %i\n", path, *(uint *)buf, buf_size);
  // open path for write only
  int fd = open(path, O_WRONLY);
  // write buffer
  write(fd, buf, buf_size);
  if (close(fd) == -1) {
    printf("Error when closing file: %d\n\r", fd);
    return PWM_SYSFS_CLOSE_ERROR;
  }
  return PWM_SUCCESS;
}

/**
 * @brief Reserve or close access to pwmchip0
 * 
 * @param reserve reservation flag 
 * @return pwm_code 
 */
pwm_code set_export(bool reserve) {
  // add an extra byte for potential terminating null
  char buf[sizeof(bool)+1];
  sprintf(buf, "%c", reserve);
  pwm_code status = ioctl(reserve ? EXPORT: UNEXPORT, &buf, sizeof(uint8_t));
  if (status != 0) {
    return status;
  }
  return PWM_SUCCESS;
}

/**
 * @brief Enable/Disable pwm channel
 * 
 * @param enable flag for enable/disable
 * @return pwm_code 
 */
pwm_code set_enable(bool enable) {
  // add an extra byte for potential terminating null
  char buf[sizeof(bool)+1];
  sprintf(buf, "%c", enable);
  pwm_code status = ioctl(ENABLE, &buf, sizeof(uint8_t));
  if (status != 0) {
    return status;
  }
  return PWM_SUCCESS;
}

/**
 * @brief Set the duty cycle of the pwm waveform in ns
 * 
 * @param duty positive pulse width in ns
 * @return pwm_code 
 */
pwm_code set_duty(uint64_t duty) {
  char buf[sizeof(uint64_t)];
  sprintf(buf, "%lld", duty);
  pwm_code status = ioctl(DUTY, &buf, sizeof(uint64_t));
  if (status != 0) {
    return status;
  }
  return PWM_SUCCESS;
}

/**
 * @brief Set the waveform pulse period in ns 
 * 
 * @param period pulse period in ns
 * @return pwm_code 
 */
pwm_code set_period(uint64_t period) {
  char buf[sizeof(uint64_t)];
  sprintf(buf, "%lld", period);
  pwm_code status = ioctl(PERIOD, &period, sizeof(uint64_t));
  if (status != 0) {
    return status;
  }
  return PWM_SUCCESS;
}

pwm_code get_status() {
  FILE *fd = exec("sudo dtparam -l");
  char output[1024];
  int tx_found = 0;
  int status;
  char indicator[] = "pwm-2chan";
  while (fgets(output, sizeof(output), fd) != NULL) {
    printf("%s\n\r", output);
    fflush(stdout);
    if (strstr(output, indicator) != NULL) {
      tx_found = 1;
    }
  }
  if (tx_found == 0) {
    fd = exec("sudo dtoverlay pwm-2chan");
  }
  status = pclose(fd);
  if (status == -1) {
    printf("Error when closing process \n\r");
  }
  return PWM_SUCCESS;
}
