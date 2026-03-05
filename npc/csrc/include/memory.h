#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "common.h"
#include "cpu.h"

//-------- mem_access ---------//

extern "C" int pROM_read(int vraddr);

extern "C" int pRAM_read(int vraddr);

extern "C" void pRAM_write(int vwaddr, int wdata, char wmask) ;

void pmem_init(int argc, char** argv);

void pmem_free();

//------- readbin -----------//
uint32_t *load_riscv32_instructions(const char *filename) ;

uint32_t* read_to_MEM(const char *fname);











#endif