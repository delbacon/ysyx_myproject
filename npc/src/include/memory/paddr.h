#ifndef __MEMORY_PADDR_H__
#define __MEMORY_PADDR_H__

#include <common.h>

#define PMEM_LEFT  ((paddr_t)CONFIG_MBASE)
#define PMEM_RIGHT ((paddr_t)CONFIG_MBASE + CONFIG_MSIZE - 1)
#define RESET_VECTOR (PMEM_LEFT + CONFIG_PC_RESET_OFFSET)

uint8_t* pROM_guest_to_host(paddr_t paddr);
/* convert the guest physical address in the guest program to host virtual address in NEMU */
uint8_t* guest_to_host(paddr_t paddr);
/* convert the host virtual address in NEMU to guest physical address in the guest program */
paddr_t host_to_guest(uint8_t *haddr);

static inline bool in_pmem(paddr_t addr) {
  return addr - CONFIG_MBASE < CONFIG_MSIZE;
}


#define CONFIG_DIFF_DEVICE_SIZE 0x1000
#define CONFIG_DIFF_DEVICE_BASE 0x10000000
static inline bool in_diff_device(paddr_t addr) {
  return addr - CONFIG_DIFF_DEVICE_BASE < CONFIG_DIFF_DEVICE_SIZE;
}


#define CONFIG_CSR_SIZE 0x1000
#define CONFIG_CSR_BASE 0x0
static inline bool in_csr(paddr_t addr) {
  return addr - CONFIG_CSR_BASE < CONFIG_CSR_SIZE;
}


word_t pROM_read(paddr_t addr);
extern "C" int pROM_read_HDL(int addr);

word_t pRAM_read(paddr_t addr, int len) ;
extern "C" int pRAM_read_HDL(int addr, int len);

void pRAM_write(paddr_t addr, int len, word_t data) ;
extern "C" void pRAM_write_HDL(int addr, int len, int data) ;

void free_pmem();

#endif