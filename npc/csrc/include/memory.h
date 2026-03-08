#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "common.h"

#define PMEM_LEFT  ((paddr_t)CONFIG_MBASE)
#define PMEM_RIGHT ((paddr_t)CONFIG_MBASE + CONFIG_MSIZE - 1)
#define RESET_VECTOR (PMEM_LEFT + CONFIG_PC_RESET_OFFSET)

//-------- mem_access ---------//
uint32_t* guest_to_host(paddr_t paddr);
paddr_t host_to_guest(uint32_t *haddr);


extern "C" int pROM_read(int vraddr);

extern "C" int pRAM_read(int vraddr);

extern "C" void pRAM_write(int vwaddr, int wdata, char wmask) ;

void pmem_init(int argc, char** argv);

void pmem_free();

//------- readbin -----------//
uint32_t *load_riscv32_instructions(const char *filename) ;

uint32_t* read_to_MEM(const char *fname);











#endif