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
#include <pthread.h>
#include "sysfs.h"


static pthread_mutex_t s_mtx;

/**
 * @brief Thread safe file I/O sysfs read
 * 
 * @param path read path
 * @param size read bytes
 * @return char* 
 */
char *rctl(const char *path, size_t size) {
  if (path == NULL) {
    error("Path cannot be null");
    return NULL;
  }
  char *buf = (char *)malloc(size);
  trace("Opening path %s for read", path);
  pthread_mutex_lock(&s_mtx);
  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    error("Error while opening %s", path);
    goto _cleanup;
  }
  ssize_t sz = read(fd, buf, size);
  info("Successful read of %d bytes: %s", sz, buf);

_cleanup:
  pthread_mutex_unlock(&s_mtx);
  return buf;
}

/**
 * @brief Thread safe I/O sysfs write
 * 
 * @param path sysfs path
 * @param buf data buffer
 * @param buf_size data buffer size in bytes
 * @return int 
 */
int wctl(const char *path, const char *buf, size_t buf_size) {
  int status;
  if (path == NULL || buf == NULL || buf_size == 0) {
    error("Invalid argument");
    return EXIT_FAILURE;
  }
  trace("Opening path %s for write of %x with size %i", path, buf, buf_size);
  pthread_mutex_lock(&s_mtx);
  // open path for write only
  int fd = open(path, O_WRONLY);
  if (fd < 0) {
    error("Error while opening %s", path);
    status = EXIT_FAILURE;
    goto _cleanup;
  }
  // write buffer
  write(fd, buf, buf_size);
  if (close(fd) == -1) {
    error("Error when closing file: %d", fd);
    status = EXIT_FAILURE;
    goto _cleanup;
  }
  info("Successful write of %d bytes: %s", buf_size, buf);
  status = EXIT_SUCCESS;

_cleanup:
  pthread_mutex_unlock(&s_mtx);
  return status;
}

/**
 * @brief Build a string repr of integer dynamically
 * 
 * @param value target integer
 * @param size size of buffer
 * @return char* 
 */
char *int64_to_str(uint64_t value, size_t *size) {
  // get length of string size
  int len = snprintf(NULL, 0, "%lu", value);
  // +1 allocation for null terminator '\0'
  *size = (size_t)len + 1;
  char *buf = malloc(*size);
  snprintf(buf, *size, "%lu", value);
  return buf;
}

/**
 * @brief Free the string pointer memory for conversion
 * 
 * @param str_alloc malloc pointer for int->str conversion
 */
void free_buffer(char *buf) {
  free(buf);
  info("Buffer freed");
}

/**
 * @brief Execute linux command and capture output
 * 
 * @param cmd 
 * @return char* 
 */
FILE *exec_linux_cmd(char *cmd) {
  FILE *fp = popen(cmd, "r");
  if (fp == NULL) {
    error("Command %s failed to execute", cmd);
    exit(EXIT_FAILURE);
  }
  return fp;
}
