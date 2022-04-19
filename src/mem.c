
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "merase.h"
#include "mem.h"

/**
 * @brief Map userspace (virtual) memory to physical memory
 * 
 * @param base peripheral start address
 * @param size size of address map to virtual memory
 * @return void* pointer to physical address space
 */
void *mem_map(uint32_t base, size_t size) {
  int mem_fd;
  trace("Request for %u bytes @ base addr: 0x%08x", size, base);
  const uint32_t offset = base % MEM_PAGE_SIZE;
  // start allocation at page base
  base = base - offset;
  // use the full page space
  size = size + offset;
  info("Mapping %u bytes @ base addr: 0x%08x", size, base);
  if ((mem_fd = open(MEM_FNAME, O_RDWR | O_SYNC)) < 0) {
    perror("Failed to open memory file descriptor. Try running with sudo.");
    return NULL;
  }
  // allow read and writes on the content
  void *mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, base);
  close(mem_fd);
  if (mem == MAP_FAILED) {
    perror("Memory map failed");
    return NULL;
  }
  // return requested start address
  return (uint8_t *)mem + offset;
}

/**
 * @brief Unmap physical memory
 * 
 * @param addr physical address pointer (from mem_map)
 * @param size size of address map
 */
void unmap_mem(void *addr, size_t size) {
  const intptr_t offset = (intptr_t)addr % MEM_PAGE_SIZE;
  addr = (uint8_t *)addr - offset;
  size = size + offset;
  if (munmap(addr, size) != 0)
    perror("munmap error");
}