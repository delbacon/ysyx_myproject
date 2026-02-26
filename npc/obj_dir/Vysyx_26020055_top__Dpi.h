// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VYSYX_26020055_TOP__DPI_H_
#define VERILATED_VYSYX_26020055_TOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_EXU.v:3:30
    extern void ebreak();
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_IFU.v:1:29
    extern int pROM_read(int raddr);
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_LSU.v:1:29
    extern int pmem_read(int raddr);
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_LSU.v:2:30
    extern void pmem_write(int waddr, int wdata, char wmask);

#ifdef __cplusplus
}
#endif

#endif  // guard
