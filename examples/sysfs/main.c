/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief Example usage of sysfs driver
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */
#include <sysfs.h>
#include <merase.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define OPTSTR ":hc:"

int shutdown();
void usage();

void usage() {
  printf(
    "Example Sysfs Driver.\n"
    "Usage:\n"
    "  ex-sysfs\n"
    "  ex-pwm -c <cmd>\n"
    "  ex-pwm -h\n\n"
    "Options:\n"
    "  -h --help      Show this screen.\n"
    "  -c <cmd>       Execute linux command\n"
  );
}

int main(int argc, char *argv[]) {
  int c, status, errflg = 0;
  char *cmd = NULL;
  merase_set_level(TRACE);
  while ((c = getopt(argc, argv, OPTSTR)) != -1) {
    switch (c) {
      case 'h':
        usage();
        exit(0);
      case 'c':
        cmd = optarg;
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
  if (cmd == NULL) {
    usage();
    exit(0);
  }
  char output[1024];
  FILE *fp = exec_linux_cmd(cmd);
  while (fgets(output, sizeof(output), fp) != NULL) {
    printf("%s", output);
  }
  char *duty = rctl(DUTY_PATH, 8);
  info("Duty Cycle: %s", duty);
  return 0;
}