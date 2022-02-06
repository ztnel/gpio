/**
 * @file sysfs.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02
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
#include "static/sysfs.h"
#include "static/errors.h"

/**
 * @brief Write data to sysfs
 * 
 * @param path sysfs path
 * @param buf data buffer
 * @param buf_size data buffer size in bytes
 * @return pwm_code 
 */
pwm_code ioctl(const char* path, const char* buf, size_t buf_size) {
  if (path == NULL || buf == NULL || buf_size == 0) {
    printf("Invalid arg\n\r");
    return PWM_ARG_ERROR;
  }
  printf("Opening path %s for write of %x with size %i\n", path, buf, buf_size);
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
 * @brief Build a string repr of integer dynamically
 * 
 * @param value target integer
 * @return char* 
 */
void int64_to_str(uint64_t value, char* buf, size_t* size) {
  // get length of string size
  int len = snprintf(NULL, 0, "%lld", value);
  // +1 allocation for null terminator '\0'
  *size = len + 1;
  buf = malloc(*size);
  snprintf(buf, *size, "%lld", value);
}

/**
 * @brief 
 * 
 * @param str_alloc 
 */
void free_buffer(char* buf) {
  free(buf);
}