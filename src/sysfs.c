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
char *rctl(const char *path, int size) {
  if (path == NULL) {
    error("Path cannot be null");
    return NULL;
  }
  char *buf = (char *)malloc((size_t)size);
  trace("Opening path %s for read", path);
  pthread_mutex_lock(&s_mtx);
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    error("Error while opening %s", path);
    goto _cleanup;
  }
  fgets(buf, size, fp);
  info("Successful read bytes: %s", buf);

_cleanup:
  fclose(fp);
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
  FILE *fp = fopen(path, "w");
  if (fp == NULL) {
    error("Error while opening %s", path);
    status = EXIT_FAILURE;
    goto _cleanup;
  }
  // write buffer
  fputs(buf, fp);
  info("Successful write of %d bytes: %s", buf_size, buf);
  status = EXIT_SUCCESS;

_cleanup:
  fclose(fp);
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
  int len = snprintf(NULL, 0, "%llu", value);
  // +1 allocation for null terminator '\0'
  *size = (size_t)len + 1;
  char *buf = malloc(*size);
  snprintf(buf, *size, "%llu", value);
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
 * @return FILE * 
 */
FILE *exec_linux_cmd(char *cmd) {
  return popen(cmd, "r");
}
