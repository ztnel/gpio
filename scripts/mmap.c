#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
  uint32_t *bcm2835_peripherals_base = 0x20000000;  
  FILE *fp;
  if ((fp = fopen("/proc/device-tree/soc/ranges" , "rb"))) {
    unsigned char buf[8];
    if (fread(buf, 1, sizeof(buf), fp) == sizeof(buf))
      bcm2835_peripherals_base = (uint32_t *)(
        buf[4] << 24 |
        buf[5] << 16 | 
        buf[6] << 8  | 
        buf[7] << 0);
    fclose(fp);
  }
  printf("Peripherals base: %lu\n", bcm2835_peripherals_base);


  // open /dev/mem device for read write. O_SYNC is to make the call blocking
  int memfd = open("/dev/mem", O_RDWR | O_SYNC);
  // create a userspace memory map for accessing gpio registers in progmem
  uint32_t *map = (uint32_t *)mmap(NULL, 4*1024, (PROT_READ | PROT_WRITE), MAP_SHARED, memfd, 0x3f200000);
  if (map == MAP_FAILED)
    printf("bcm2835_init: mmap failed: %s\n", strerror(errno));    
  // close the memory file
  close(memfd);

  // create a volatile address pointer to prevent compiler optimization
  volatile uint32_t *paddr = map;
  /* GPIO4 is controlled by the FSEL0 register and bits 12 13 14.
  These should be configured as output which corresponds to 001 (output):
  
  0 0 0  0 0 0  0 0 0  0 0 0  0 0 1  0 0 0  0 0 0  0 0 0  0 0 0  0 0 0  0 0
  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----
  GPIO0  GPIO1  GPIO2  GPIO3  GPIO4  GPIO5  GPIO6  GPIO7  GPIO8  GPIO9
  
  Therefore the FSEL0 register should be loaded with 0x1000*/
  *paddr=0x1000;
  // SET0 register
  volatile uint32_t *paddr1 = map + 0x1C/4;
  // CLR0 register
  volatile uint32_t *paddr2 = map + 0x28/4;
  // toggle the set and clear0 register as fast a possible
  for(;;) {
    *paddr1=0x10;
    *paddr2=0x10;
  };
  return (EXIT_SUCCESS);
}