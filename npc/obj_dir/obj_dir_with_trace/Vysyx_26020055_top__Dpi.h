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
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_LSU.v:1:29
    extern int pRAM_read(int vraddr);
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_LSU.v:2:30
    extern void pRAM_write(int vwaddr, int wdata, char wmask);
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_IFU.v:1:29
    extern int pROM_read(int vraddr);
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_WBU.v:2:30
    extern void pc_get(int val);
    // DPI import at /home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_RegisterFile.v:1:30
    extern void reg_get(int reg_idx, int val);

#ifdef __cplusplus
}
#endif

#endif  // guard
