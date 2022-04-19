/**
 * @file mem.h
 * @author ztnel (christian.sargusingh@gbatteries.com)
 * @brief Peripheral memory mapping interface
 * @version 0.1
 * @date 2022-04
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#ifndef MEM_H_
#define MEM_H_

#include <stdint.h>
#include <stddef.h>


/**
 * @brief For more about Raspberry Pi's peripheral mapping:
 * https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf
 */
#define MEM_BCM2711_BASE        0xFE000000
#define MEM_PAGE_SIZE           4096
#define MEM_FNAME               "/dev/mem"

void *mem_map(uint32_t base, size_t size);
void mem_unmap(void *map, size_t size);

#endif  // MEM_H_