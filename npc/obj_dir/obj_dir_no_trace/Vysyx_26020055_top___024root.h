// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_26020055_top.h for the primary calling header

#ifndef VERILATED_VYSYX_26020055_TOP___024ROOT_H_
#define VERILATED_VYSYX_26020055_TOP___024ROOT_H_  // guard

#include "verilated.h"
class Vysyx_26020055_top___024unit;


class Vysyx_26020055_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vysyx_26020055_top___024root final {
  public:
    // CELLS
    Vysyx_26020055_top___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_OUT8(jmp_op,3,0);
    CData/*5:0*/ ysyx_26020055_top__DOT__exu_op;
    CData/*3:0*/ ysyx_26020055_top__DOT__mem_op;
    CData/*0:0*/ ysyx_26020055_top__DOT____Vcellinp__EXU__mem_on;
    CData/*0:0*/ ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_2;
    CData/*0:0*/ ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_5;
    CData/*7:0*/ ysyx_26020055_top__DOT__LSU__DOT__wmask;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_OUT(pc,31,0);
    VL_OUT(inst,31,0);
    IData/*31:0*/ ysyx_26020055_top__DOT__rs1_data;
    IData/*31:0*/ ysyx_26020055_top__DOT__rs2_data;
    IData/*31:0*/ ysyx_26020055_top__DOT__rdata;
    IData/*31:0*/ ysyx_26020055_top__DOT__EXU__DOT__imm;
    IData/*31:0*/ ysyx_26020055_top__DOT__EXU__DOT__src2;
    IData/*31:0*/ ysyx_26020055_top__DOT__EXU__DOT__alu_out;
    IData/*31:0*/ ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata;
    IData/*31:0*/ ysyx_26020055_top__DOT__WBU__DOT__next_pc;
    IData/*31:0*/ __Vfunc_pROM_read__0__Vfuncout;
    IData/*31:0*/ __Vfunc_pRAM_read__3__Vfuncout;
    IData/*16:0*/ __VdfgRegularize_h6e95ff9d_0_0;
    IData/*31:0*/ __VactIterCount;
    QData/*32:0*/ ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res;
    VlUnpacked<IData/*31:0*/, 32> ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vysyx_26020055_top__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vysyx_26020055_top___024root(Vysyx_26020055_top__Syms* symsp, const char* namep);
    ~Vysyx_26020055_top___024root();
    VL_UNCOPYABLE(Vysyx_26020055_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
