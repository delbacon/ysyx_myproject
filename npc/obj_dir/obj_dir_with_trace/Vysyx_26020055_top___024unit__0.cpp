// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_26020055_top.h for the primary calling header

#include "Vysyx_26020055_top__pch.h"

extern "C" void ebreak();

void Vysyx_26020055_top___024unit____Vdpiimwrap_ebreak_TOP____024unit() {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_26020055_top___024unit____Vdpiimwrap_ebreak_TOP____024unit\n"); );
    // Body
    ebreak();
}

extern "C" int pROM_read(int vraddr);

void Vysyx_26020055_top___024unit____Vdpiimwrap_pROM_read_TOP____024unit(IData/*31:0*/ vraddr, IData/*31:0*/ &pROM_read__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_26020055_top___024unit____Vdpiimwrap_pROM_read_TOP____024unit\n"); );
    // Body
    int vraddr__Vcvt;
    vraddr__Vcvt = vraddr;
    int pROM_read__Vfuncrtn__Vcvt;
    pROM_read__Vfuncrtn__Vcvt = pROM_read(vraddr__Vcvt);
    pROM_read__Vfuncrtn = (pROM_read__Vfuncrtn__Vcvt);
}

extern "C" void pc_get(int val);

void Vysyx_26020055_top___024unit____Vdpiimwrap_pc_get_TOP____024unit(IData/*31:0*/ val) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_26020055_top___024unit____Vdpiimwrap_pc_get_TOP____024unit\n"); );
    // Body
    int val__Vcvt;
    val__Vcvt = val;
    pc_get(val__Vcvt);
}

extern "C" void reg_get(int reg_idx, int val);

void Vysyx_26020055_top___024unit____Vdpiimwrap_reg_get_TOP____024unit(IData/*31:0*/ reg_idx, IData/*31:0*/ val) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_26020055_top___024unit____Vdpiimwrap_reg_get_TOP____024unit\n"); );
    // Body
    int reg_idx__Vcvt;
    reg_idx__Vcvt = reg_idx;
    int val__Vcvt;
    val__Vcvt = val;
    reg_get(reg_idx__Vcvt, val__Vcvt);
}

extern "C" int pRAM_read(int vraddr);

void Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_read_TOP____024unit(IData/*31:0*/ vraddr, IData/*31:0*/ &pRAM_read__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_read_TOP____024unit\n"); );
    // Body
    int vraddr__Vcvt;
    vraddr__Vcvt = vraddr;
    int pRAM_read__Vfuncrtn__Vcvt;
    pRAM_read__Vfuncrtn__Vcvt = pRAM_read(vraddr__Vcvt);
    pRAM_read__Vfuncrtn = (pRAM_read__Vfuncrtn__Vcvt);
}

extern "C" void pRAM_write(int vwaddr, int wdata, char wmask);

void Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_write_TOP____024unit(IData/*31:0*/ vwaddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_write_TOP____024unit\n"); );
    // Body
    int vwaddr__Vcvt;
    vwaddr__Vcvt = vwaddr;
    int wdata__Vcvt;
    wdata__Vcvt = wdata;
    char wmask__Vcvt;
    wmask__Vcvt = wmask;
    pRAM_write(vwaddr__Vcvt, wdata__Vcvt, wmask__Vcvt);
}
