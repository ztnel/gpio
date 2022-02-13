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
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <merase.h>
#include "sysfs.h"
#include "errors.h"


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
    error("Invalid arg");
    return PWM_ARG_ERROR;
  }
  trace("Opening path %s for write of %x with size %i", path, buf, buf_size);
  // open path for write only
  int fd = open(path, O_WRONLY);
  // write buffer
  write(fd, buf, buf_size);
  if (close(fd) == -1) {
    error("Error when closing file: %d", fd);
    return PWM_SYSFS_CLOSE_ERROR;
  }
  return PWM_SUCCESS;
}

/**
 * @brief Build a string repr of integer dynamically
 * 
 * @param value target integer
 * @param size size of buffer
 * @return char* 
 */
char* int64_to_str(uint64_t value, size_t* size) {
  // get length of string size
  int len = snprintf(NULL, 0, "%lld", value);
  // +1 allocation for null terminator '\0'
  *size = (size_t)len + 1;
  char *buf = malloc(*size);
  snprintf(buf, *size, "%lld", value);
  return buf;
}

/**
 * @brief Free the string pointer memory for conversion
 * 
 * @param str_alloc malloc pointer for int->str conversion
 */
void free_buffer(char* buf) {
  free(buf);
  info("String buffer freed");
}