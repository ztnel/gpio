/**
 * @file sysfs.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#ifndef SYSFS_H_
#define SYSFS_H_

#include <stdint.h>
#include <stdio.h>
#include "errors.h"


char *rctl(const char *path, int buf_size);
int wctl(const char *path, const char *buf, size_t buf_size);
char *int64_to_str(uint64_t value, size_t *size);
void free_buffer(char *buf);
FILE *exec_linux_cmd(char *cmd);

#endif  // SYSFS_H_
