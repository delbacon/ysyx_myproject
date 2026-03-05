// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_26020055_top.h for the primary calling header

#include "Vysyx_26020055_top__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_26020055_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vysyx_26020055_top___024root___eval_triggers__act(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_triggers__act\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_26020055_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vysyx_26020055_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vysyx_26020055_top___024unit____Vdpiimwrap_pc_get_TOP____024unit(IData/*31:0*/ val);
void Vysyx_26020055_top___024unit____Vdpiimwrap_reg_get_TOP____024unit(IData/*31:0*/ reg_idx, IData/*31:0*/ val);
void Vysyx_26020055_top___024unit____Vdpiimwrap_pROM_read_TOP____024unit(IData/*31:0*/ vraddr, IData/*31:0*/ &pROM_read__Vfuncrtn);
void Vysyx_26020055_top___024unit____Vdpiimwrap_ebreak_TOP____024unit();
void Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_read_TOP____024unit(IData/*31:0*/ vraddr, IData/*31:0*/ &pRAM_read__Vfuncrtn);
void Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_write_TOP____024unit(IData/*31:0*/ vwaddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

void Vysyx_26020055_top___024root___nba_sequent__TOP__0(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___nba_sequent__TOP__0\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VdlyVal__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0;
    __VdlyVal__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0 = 0;
    CData/*4:0*/ __VdlyDim0__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0;
    __VdlyDim0__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0 = 0;
    CData/*0:0*/ __VdlySet__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0;
    __VdlySet__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0 = 0;
    // Body
    Vysyx_26020055_top___024unit____Vdpiimwrap_pc_get_TOP____024unit(vlSelfRef.pc);
    __VdlySet__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0 = 0U;
    vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__unnamedblk1__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000020U, vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__unnamedblk1__DOT__i)) {
        Vysyx_26020055_top___024unit____Vdpiimwrap_reg_get_TOP____024unit(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__unnamedblk1__DOT__i, 
                                                                          vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf
                                                                          [
                                                                          (0x0000001fU 
                                                                           & vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__unnamedblk1__DOT__i)]);
        vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__unnamedblk1__DOT__i 
            = ((IData)(1U) + vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__unnamedblk1__DOT__i);
    }
    if ((((0x33U == (0x0000007fU & vlSelfRef.inst)) 
          | ((0x3bU == (0x0000007fU & vlSelfRef.inst)) 
             | ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_5) 
                | ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_2) 
                   | ((0x6fU == (0x0000007fU & vlSelfRef.inst)) 
                      | (0x63U == (0x0000007fU & vlSelfRef.inst))))))) 
         & (0U != (0x0000001fU & (vlSelfRef.inst >> 7U))))) {
        __VdlyVal__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0 
            = ((2U == (IData)(vlSelfRef.jmp_op)) ? 
               ((2U == (IData)(vlSelfRef.jmp_op)) ? 
                ((IData)(4U) + vlSelfRef.pc) : 0U) : 
               ((1U == ((0x00000037U == (0x0000007fU 
                                         & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                         ? 1U : 0U)) ? ((1U == ((0x00000037U 
                                                 == 
                                                 (0x0000007fU 
                                                  & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                 ? 1U
                                                 : 0U))
                                         ? vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm
                                         : 0U) : ((IData)(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__mem_on)
                                                   ? vlSelfRef.ysyx_26020055_top__DOT__rdata
                                                   : vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out)));
        __VdlyDim0__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0 
            = (0x0000001fU & (vlSelfRef.inst >> 7U));
        __VdlySet__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0 = 1U;
    }
    if (__VdlySet__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0) {
        vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[__VdlyDim0__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0] 
            = __VdlyVal__ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf__v0;
    }
    vlSelfRef.pc = ((IData)(vlSelfRef.rst) ? 0x80000000U
                     : vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__next_pc);
    Vysyx_26020055_top___024unit____Vdpiimwrap_pROM_read_TOP____024unit(vlSelfRef.pc, vlSelfRef.__Vfunc_pROM_read__0__Vfuncout);
    vlSelfRef.inst = vlSelfRef.__Vfunc_pROM_read__0__Vfuncout;
    if ((2U == ((0x00100073U == vlSelfRef.inst) ? 2U
                 : 0U))) {
        Vysyx_26020055_top___024unit____Vdpiimwrap_ebreak_TOP____024unit();
    }
    if (((((((((0x00000067U == (0x000003ffU & ((0x0001fc00U 
                                                & (vlSelfRef.inst 
                                                   >> 0x0000000fU)) 
                                               | ((0x00000380U 
                                                   & (vlSelfRef.inst 
                                                      >> 5U)) 
                                                  | (0x0000007fU 
                                                     & vlSelfRef.inst))))) 
               | (0x00000033U == ((0x0001fc00U & (vlSelfRef.inst 
                                                  >> 0x0000000fU)) 
                                  | ((0x00000380U & 
                                      (vlSelfRef.inst 
                                       >> 5U)) | (0x0000007fU 
                                                  & vlSelfRef.inst))))) 
              | (((((0x00000013U == (0x000003ffU & 
                                     ((0x0001fc00U 
                                       & (vlSelfRef.inst 
                                          >> 0x0000000fU)) 
                                      | ((0x00000380U 
                                          & (vlSelfRef.inst 
                                             >> 5U)) 
                                         | (0x0000007fU 
                                            & vlSelfRef.inst))))) 
                    || (0x00000103U == (0x000003ffU 
                                        & ((0x0001fc00U 
                                            & (vlSelfRef.inst 
                                               >> 0x0000000fU)) 
                                           | ((0x00000380U 
                                               & (vlSelfRef.inst 
                                                  >> 5U)) 
                                              | (0x0000007fU 
                                                 & vlSelfRef.inst)))))) 
                   || (0x00000123U == (0x000003ffU 
                                       & ((0x0001fc00U 
                                           & (vlSelfRef.inst 
                                              >> 0x0000000fU)) 
                                          | ((0x00000380U 
                                              & (vlSelfRef.inst 
                                                 >> 5U)) 
                                             | (0x0000007fU 
                                                & vlSelfRef.inst)))))) 
                  || (0x00000203U == (0x000003ffU & 
                                      ((0x0001fc00U 
                                        & (vlSelfRef.inst 
                                           >> 0x0000000fU)) 
                                       | ((0x00000380U 
                                           & (vlSelfRef.inst 
                                              >> 5U)) 
                                          | (0x0000007fU 
                                             & vlSelfRef.inst)))))) 
                 || (0x00000023U == (0x000003ffU & 
                                     ((0x0001fc00U 
                                       & (vlSelfRef.inst 
                                          >> 0x0000000fU)) 
                                      | ((0x00000380U 
                                          & (vlSelfRef.inst 
                                             >> 5U)) 
                                         | (0x0000007fU 
                                            & vlSelfRef.inst))))))) 
             | (4U == ((0x0001fc00U & (vlSelfRef.inst 
                                       >> 0x0000000fU)) 
                       | ((0x00000380U & (vlSelfRef.inst 
                                          >> 5U)) | 
                          (0x0000007fU & vlSelfRef.inst))))) 
            | (5U == ((0x0001fc00U & (vlSelfRef.inst 
                                      >> 0x0000000fU)) 
                      | ((0x00000380U & (vlSelfRef.inst 
                                         >> 5U)) | 
                         (0x0000007fU & vlSelfRef.inst))))) 
           | (0U == ((0x0001fc00U & (vlSelfRef.inst 
                                     >> 0x0000000fU)) 
                     | ((0x00000380U & (vlSelfRef.inst 
                                        >> 5U)) | (0x0000007fU 
                                                   & vlSelfRef.inst))))) 
          | (1U == ((0x0001fc00U & (vlSelfRef.inst 
                                    >> 0x0000000fU)) 
                    | ((0x00000380U & (vlSelfRef.inst 
                                       >> 5U)) | (0x0000007fU 
                                                  & vlSelfRef.inst))))) 
         | (4U == ((0x0001fc00U & (vlSelfRef.inst >> 0x0000000fU)) 
                   | ((0x00000380U & (vlSelfRef.inst 
                                      >> 5U)) | (0x0000007fU 
                                                 & vlSelfRef.inst)))))) {
        if ((0x00000067U == (0x000003ffU & ((0x0001fc00U 
                                             & (vlSelfRef.inst 
                                                >> 0x0000000fU)) 
                                            | ((0x00000380U 
                                                & (vlSelfRef.inst 
                                                   >> 5U)) 
                                               | (0x0000007fU 
                                                  & vlSelfRef.inst)))))) {
            vlSelfRef.jmp_op = 2U;
            vlSelfRef.ysyx_26020055_top__DOT__exu_op = 0U;
        } else {
            vlSelfRef.jmp_op = 0U;
            vlSelfRef.ysyx_26020055_top__DOT__exu_op 
                = ((0x00000033U == ((0x0001fc00U & 
                                     (vlSelfRef.inst 
                                      >> 0x0000000fU)) 
                                    | ((0x00000380U 
                                        & (vlSelfRef.inst 
                                           >> 5U)) 
                                       | (0x0000007fU 
                                          & vlSelfRef.inst))))
                    ? 0U : ((((((0x00000013U == (0x000003ffU 
                                                 & ((0x0001fc00U 
                                                     & (vlSelfRef.inst 
                                                        >> 0x0000000fU)) 
                                                    | ((0x00000380U 
                                                        & (vlSelfRef.inst 
                                                           >> 5U)) 
                                                       | (0x0000007fU 
                                                          & vlSelfRef.inst))))) 
                                || (0x00000103U == 
                                    (0x000003ffU & 
                                     ((0x0001fc00U 
                                       & (vlSelfRef.inst 
                                          >> 0x0000000fU)) 
                                      | ((0x00000380U 
                                          & (vlSelfRef.inst 
                                             >> 5U)) 
                                         | (0x0000007fU 
                                            & vlSelfRef.inst)))))) 
                               || (0x00000123U == (0x000003ffU 
                                                   & ((0x0001fc00U 
                                                       & (vlSelfRef.inst 
                                                          >> 0x0000000fU)) 
                                                      | ((0x00000380U 
                                                          & (vlSelfRef.inst 
                                                             >> 5U)) 
                                                         | (0x0000007fU 
                                                            & vlSelfRef.inst)))))) 
                              || (0x00000203U == (0x000003ffU 
                                                  & ((0x0001fc00U 
                                                      & (vlSelfRef.inst 
                                                         >> 0x0000000fU)) 
                                                     | ((0x00000380U 
                                                         & (vlSelfRef.inst 
                                                            >> 5U)) 
                                                        | (0x0000007fU 
                                                           & vlSelfRef.inst)))))) 
                             || (0x00000023U == (0x000003ffU 
                                                 & ((0x0001fc00U 
                                                     & (vlSelfRef.inst 
                                                        >> 0x0000000fU)) 
                                                    | ((0x00000380U 
                                                        & (vlSelfRef.inst 
                                                           >> 5U)) 
                                                       | (0x0000007fU 
                                                          & vlSelfRef.inst))))))
                             ? 0x20U : ((4U == ((0x0001fc00U 
                                                 & (vlSelfRef.inst 
                                                    >> 0x0000000fU)) 
                                                | ((0x00000380U 
                                                    & (vlSelfRef.inst 
                                                       >> 5U)) 
                                                   | (0x0000007fU 
                                                      & vlSelfRef.inst))))
                                         ? 1U : ((5U 
                                                  == 
                                                  ((0x0001fc00U 
                                                    & (vlSelfRef.inst 
                                                       >> 0x0000000fU)) 
                                                   | ((0x00000380U 
                                                       & (vlSelfRef.inst 
                                                          >> 5U)) 
                                                      | (0x0000007fU 
                                                         & vlSelfRef.inst))))
                                                  ? 0x21U
                                                  : 
                                                 ((0U 
                                                   == 
                                                   ((0x0001fc00U 
                                                     & (vlSelfRef.inst 
                                                        >> 0x0000000fU)) 
                                                    | ((0x00000380U 
                                                        & (vlSelfRef.inst 
                                                           >> 5U)) 
                                                       | (0x0000007fU 
                                                          & vlSelfRef.inst))))
                                                   ? 2U
                                                   : 
                                                  ((1U 
                                                    == 
                                                    ((0x0001fc00U 
                                                      & (vlSelfRef.inst 
                                                         >> 0x0000000fU)) 
                                                     | ((0x00000380U 
                                                         & (vlSelfRef.inst 
                                                            >> 5U)) 
                                                        | (0x0000007fU 
                                                           & vlSelfRef.inst))))
                                                    ? 0x22U
                                                    : 3U))))));
        }
    } else {
        vlSelfRef.jmp_op = 0U;
        vlSelfRef.ysyx_26020055_top__DOT__exu_op = 
            (((((((((5U == ((0x0001fc00U & (vlSelfRef.inst 
                                            >> 0x0000000fU)) 
                            | ((0x00000380U & (vlSelfRef.inst 
                                               >> 5U)) 
                               | (0x0000007fU & vlSelfRef.inst)))) 
                    | (6U == ((0x0001fc00U & (vlSelfRef.inst 
                                              >> 0x0000000fU)) 
                              | ((0x00000380U & (vlSelfRef.inst 
                                                 >> 5U)) 
                                 | (0x0000007fU & vlSelfRef.inst))))) 
                   | (7U == ((0x0001fc00U & (vlSelfRef.inst 
                                             >> 0x0000000fU)) 
                             | ((0x00000380U & (vlSelfRef.inst 
                                                >> 5U)) 
                                | (0x0000007fU & vlSelfRef.inst))))) 
                  | (0U == ((0x0001fc00U & (vlSelfRef.inst 
                                            >> 0x0000000fU)) 
                            | ((0x00000380U & (vlSelfRef.inst 
                                               >> 5U)) 
                               | (0x0000007fU & vlSelfRef.inst))))) 
                 | (1U == ((0x0001fc00U & (vlSelfRef.inst 
                                           >> 0x0000000fU)) 
                           | ((0x00000380U & (vlSelfRef.inst 
                                              >> 5U)) 
                              | (0x0000007fU & vlSelfRef.inst))))) 
                | (4U == ((0x0001fc00U & (vlSelfRef.inst 
                                          >> 0x0000000fU)) 
                          | ((0x00000380U & (vlSelfRef.inst 
                                             >> 5U)) 
                             | (0x0000007fU & vlSelfRef.inst))))) 
               | (5U == ((0x0001fc00U & (vlSelfRef.inst 
                                         >> 0x0000000fU)) 
                         | ((0x00000380U & (vlSelfRef.inst 
                                            >> 5U)) 
                            | (0x0000007fU & vlSelfRef.inst))))) 
              | (0U == ((0x0001fc00U & (vlSelfRef.inst 
                                        >> 0x0000000fU)) 
                        | ((0x00000380U & (vlSelfRef.inst 
                                           >> 5U)) 
                           | (0x0000007fU & vlSelfRef.inst)))))
              ? ((5U == ((0x0001fc00U & (vlSelfRef.inst 
                                         >> 0x0000000fU)) 
                         | ((0x00000380U & (vlSelfRef.inst 
                                            >> 5U)) 
                            | (0x0000007fU & vlSelfRef.inst))))
                  ? 0x23U : ((6U == ((0x0001fc00U & 
                                      (vlSelfRef.inst 
                                       >> 0x0000000fU)) 
                                     | ((0x00000380U 
                                         & (vlSelfRef.inst 
                                            >> 5U)) 
                                        | (0x0000007fU 
                                           & vlSelfRef.inst))))
                              ? 5U : ((7U == ((0x0001fc00U 
                                               & (vlSelfRef.inst 
                                                  >> 0x0000000fU)) 
                                              | ((0x00000380U 
                                                  & (vlSelfRef.inst 
                                                     >> 5U)) 
                                                 | (0x0000007fU 
                                                    & vlSelfRef.inst))))
                                       ? 0x25U : ((0U 
                                                   == 
                                                   ((0x0001fc00U 
                                                     & (vlSelfRef.inst 
                                                        >> 0x0000000fU)) 
                                                    | ((0x00000380U 
                                                        & (vlSelfRef.inst 
                                                           >> 5U)) 
                                                       | (0x0000007fU 
                                                          & vlSelfRef.inst))))
                                                   ? 6U
                                                   : 
                                                  ((1U 
                                                    == 
                                                    ((0x0001fc00U 
                                                      & (vlSelfRef.inst 
                                                         >> 0x0000000fU)) 
                                                     | ((0x00000380U 
                                                         & (vlSelfRef.inst 
                                                            >> 5U)) 
                                                        | (0x0000007fU 
                                                           & vlSelfRef.inst))))
                                                    ? 0x26U
                                                    : 
                                                   ((4U 
                                                     == 
                                                     ((0x0001fc00U 
                                                       & (vlSelfRef.inst 
                                                          >> 0x0000000fU)) 
                                                      | ((0x00000380U 
                                                          & (vlSelfRef.inst 
                                                             >> 5U)) 
                                                         | (0x0000007fU 
                                                            & vlSelfRef.inst))))
                                                     ? 7U
                                                     : 
                                                    ((5U 
                                                      == 
                                                      ((0x0001fc00U 
                                                        & (vlSelfRef.inst 
                                                           >> 0x0000000fU)) 
                                                       | ((0x00000380U 
                                                           & (vlSelfRef.inst 
                                                              >> 5U)) 
                                                          | (0x0000007fU 
                                                             & vlSelfRef.inst))))
                                                      ? 0x27U
                                                      : 8U)))))))
              : (((((((((1U == ((0x0001fc00U & (vlSelfRef.inst 
                                                >> 0x0000000fU)) 
                                | ((0x00000380U & (vlSelfRef.inst 
                                                   >> 5U)) 
                                   | (0x0000007fU & vlSelfRef.inst)))) 
                        | (4U == ((0x0001fc00U & (vlSelfRef.inst 
                                                  >> 0x0000000fU)) 
                                  | ((0x00000380U & 
                                      (vlSelfRef.inst 
                                       >> 5U)) | (0x0000007fU 
                                                  & vlSelfRef.inst))))) 
                       | (5U == ((0x0001fc00U & (vlSelfRef.inst 
                                                 >> 0x0000000fU)) 
                                 | ((0x00000380U & 
                                     (vlSelfRef.inst 
                                      >> 5U)) | (0x0000007fU 
                                                 & vlSelfRef.inst))))) 
                      | (8U == ((0x0001fc00U & (vlSelfRef.inst 
                                                >> 0x0000000fU)) 
                                | ((0x00000380U & (vlSelfRef.inst 
                                                   >> 5U)) 
                                   | (0x0000007fU & vlSelfRef.inst))))) 
                     | (9U == ((0x0001fc00U & (vlSelfRef.inst 
                                               >> 0x0000000fU)) 
                               | ((0x00000380U & (vlSelfRef.inst 
                                                  >> 5U)) 
                                  | (0x0000007fU & vlSelfRef.inst))))) 
                    | (0x0000000cU == ((0x0001fc00U 
                                        & (vlSelfRef.inst 
                                           >> 0x0000000fU)) 
                                       | ((0x00000380U 
                                           & (vlSelfRef.inst 
                                              >> 5U)) 
                                          | (0x0000007fU 
                                             & vlSelfRef.inst))))) 
                   | (0x0000000dU == ((0x0001fc00U 
                                       & (vlSelfRef.inst 
                                          >> 0x0000000fU)) 
                                      | ((0x00000380U 
                                          & (vlSelfRef.inst 
                                             >> 5U)) 
                                         | (0x0000007fU 
                                            & vlSelfRef.inst))))) 
                  | (0x0000000eU == ((0x0001fc00U & 
                                      (vlSelfRef.inst 
                                       >> 0x0000000fU)) 
                                     | ((0x00000380U 
                                         & (vlSelfRef.inst 
                                            >> 5U)) 
                                        | (0x0000007fU 
                                           & vlSelfRef.inst)))))
                  ? ((1U == ((0x0001fc00U & (vlSelfRef.inst 
                                             >> 0x0000000fU)) 
                             | ((0x00000380U & (vlSelfRef.inst 
                                                >> 5U)) 
                                | (0x0000007fU & vlSelfRef.inst))))
                      ? 0x28U : ((4U == ((0x0001fc00U 
                                          & (vlSelfRef.inst 
                                             >> 0x0000000fU)) 
                                         | ((0x00000380U 
                                             & (vlSelfRef.inst 
                                                >> 5U)) 
                                            | (0x0000007fU 
                                               & vlSelfRef.inst))))
                                  ? 9U : ((5U == ((0x0001fc00U 
                                                   & (vlSelfRef.inst 
                                                      >> 0x0000000fU)) 
                                                  | ((0x00000380U 
                                                      & (vlSelfRef.inst 
                                                         >> 5U)) 
                                                     | (0x0000007fU 
                                                        & vlSelfRef.inst))))
                                           ? 0x29U : 
                                          ((8U == (
                                                   (0x0001fc00U 
                                                    & (vlSelfRef.inst 
                                                       >> 0x0000000fU)) 
                                                   | ((0x00000380U 
                                                       & (vlSelfRef.inst 
                                                          >> 5U)) 
                                                      | (0x0000007fU 
                                                         & vlSelfRef.inst))))
                                            ? 0x0aU
                                            : ((9U 
                                                == 
                                                ((0x0001fc00U 
                                                  & (vlSelfRef.inst 
                                                     >> 0x0000000fU)) 
                                                 | ((0x00000380U 
                                                     & (vlSelfRef.inst 
                                                        >> 5U)) 
                                                    | (0x0000007fU 
                                                       & vlSelfRef.inst))))
                                                ? 0x2aU
                                                : (
                                                   (0x0000000cU 
                                                    == 
                                                    ((0x0001fc00U 
                                                      & (vlSelfRef.inst 
                                                         >> 0x0000000fU)) 
                                                     | ((0x00000380U 
                                                         & (vlSelfRef.inst 
                                                            >> 5U)) 
                                                        | (0x0000007fU 
                                                           & vlSelfRef.inst))))
                                                    ? 0x0bU
                                                    : 
                                                   ((0x0000000dU 
                                                     == 
                                                     ((0x0001fc00U 
                                                       & (vlSelfRef.inst 
                                                          >> 0x0000000fU)) 
                                                      | ((0x00000380U 
                                                          & (vlSelfRef.inst 
                                                             >> 5U)) 
                                                         | (0x0000007fU 
                                                            & vlSelfRef.inst))))
                                                     ? 0x2bU
                                                     : 0x0cU)))))))
                  : ((0x0000000fU == ((0x0001fc00U 
                                       & (vlSelfRef.inst 
                                          >> 0x0000000fU)) 
                                      | ((0x00000380U 
                                          & (vlSelfRef.inst 
                                             >> 5U)) 
                                         | (0x0000007fU 
                                            & vlSelfRef.inst))))
                      ? 0x2cU : 0U)));
    }
    vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__mem_on 
        = ((3U == (0x0000007fU & vlSelfRef.inst)) | 
           (0x23U == (0x0000007fU & vlSelfRef.inst)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = ((0x0001fc00U 
                                                 & (vlSelfRef.inst 
                                                    >> 0x0000000fU)) 
                                                | ((0x00000380U 
                                                    & (vlSelfRef.inst 
                                                       >> 5U)) 
                                                   | (0x0000007fU 
                                                      & vlSelfRef.inst)));
    vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
        = ((0U == (0x0000001fU & (vlSelfRef.inst >> 0x0000000fU)))
            ? 0U : vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf
           [(0x0000001fU & (vlSelfRef.inst >> 0x0000000fU))]);
    vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_5 
        = ((0x67U == (0x0000007fU & vlSelfRef.inst)) 
           | ((3U == (0x0000007fU & vlSelfRef.inst)) 
              | (0x13U == (0x0000007fU & vlSelfRef.inst))));
    vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_2 
        = ((0x37U == (0x0000007fU & vlSelfRef.inst)) 
           | (0x17U == (0x0000007fU & vlSelfRef.inst)));
    vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs2_data 
        = ((0U == (0x0000001fU & (vlSelfRef.inst >> 0x00000014U)))
            ? 0U : vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf
           [(0x0000001fU & (vlSelfRef.inst >> 0x00000014U))]);
    vlSelfRef.ysyx_26020055_top__DOT__mem_op = ((0x00000203U 
                                                 == 
                                                 (0x000003ffU 
                                                  & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                 ? 1U
                                                 : 
                                                (((3U 
                                                   == 
                                                   (0x000003ffU 
                                                    & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)) 
                                                  | (0x00000023U 
                                                     == 
                                                     (0x000003ffU 
                                                      & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)))
                                                  ? 9U
                                                  : 
                                                 ((0x00000283U 
                                                   == 
                                                   (0x000003ffU 
                                                    & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                   ? 2U
                                                   : 
                                                  (((0x00000083U 
                                                     == 
                                                     (0x000003ffU 
                                                      & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)) 
                                                    | (0x000000a3U 
                                                       == 
                                                       (0x000003ffU 
                                                        & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)))
                                                    ? 0x0aU
                                                    : 
                                                   (((0x00000103U 
                                                      == 
                                                      (0x000003ffU 
                                                       & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)) 
                                                     | (0x00000123U 
                                                        == 
                                                        (0x000003ffU 
                                                         & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)))
                                                     ? 3U
                                                     : 0U)))));
    vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm 
        = ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_5)
            ? (((- (IData)((vlSelfRef.inst >> 0x0000001fU))) 
                << 0x0000000cU) | (vlSelfRef.inst >> 0x00000014U))
            : ((0x23U == (0x0000007fU & vlSelfRef.inst))
                ? (((- (IData)((vlSelfRef.inst >> 0x0000001fU))) 
                    << 0x0000000cU) | ((0x00000fe0U 
                                        & (vlSelfRef.inst 
                                           >> 0x00000014U)) 
                                       | (0x0000001fU 
                                          & (vlSelfRef.inst 
                                             >> 7U))))
                : ((0x63U == (0x0000007fU & vlSelfRef.inst))
                    ? (((- (IData)((vlSelfRef.inst 
                                    >> 0x0000001fU))) 
                        << 0x0000000cU) | ((0x00000800U 
                                            & (vlSelfRef.inst 
                                               << 4U)) 
                                           | ((0x000007e0U 
                                               & (vlSelfRef.inst 
                                                  >> 0x00000014U)) 
                                              | (0x0000001eU 
                                                 & (vlSelfRef.inst 
                                                    >> 7U)))))
                    : ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_2)
                        ? (0xfffff000U & vlSelfRef.inst)
                        : ((0x6fU == (0x0000007fU & vlSelfRef.inst))
                            ? (((- (IData)((vlSelfRef.inst 
                                            >> 0x0000001fU))) 
                                << 0x00000014U) | (
                                                   (((0x000001feU 
                                                      & (vlSelfRef.inst 
                                                         >> 0x0000000bU)) 
                                                     | (1U 
                                                        & (vlSelfRef.inst 
                                                           >> 0x00000014U))) 
                                                    << 0x0000000bU) 
                                                   | (0x000007feU 
                                                      & (vlSelfRef.inst 
                                                         >> 0x00000014U))))
                            : 0U)))));
    vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__next_pc 
        = ((2U == (IData)(vlSelfRef.jmp_op)) ? ((2U 
                                                 == (IData)(vlSelfRef.jmp_op))
                                                 ? 
                                                (0xfffffffeU 
                                                 & (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                                    + vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm))
                                                 : 0U)
            : ((IData)(4U) + vlSelfRef.pc));
    vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
        = ((0x00000020U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op))
            ? vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm
            : vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs2_data);
    if (((((((((0U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op))) 
               | (1U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) 
              | (2U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) 
             | (3U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) 
            | (4U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) 
           | (5U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) 
          | (6U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) 
         | (7U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op))))) {
        if ((0U != (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
            if ((1U != (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
                vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out 
                    = ((2U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                        ? (VL_LTS_III(32, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2)
                            ? 1U : 0U) : ((3U == (0x0000000fU 
                                                  & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                                           ? (VL_GTS_III(32, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2)
                                               ? 1U
                                               : 0U)
                                           : ((4U == 
                                               (0x0000000fU 
                                                & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                                               ? ((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                                   == vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2)
                                                   ? 1U
                                                   : 0U)
                                               : ((5U 
                                                   == 
                                                   (0x0000000fU 
                                                    & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                                                   ? 
                                                  ((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                                    < vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2)
                                                    ? 1U
                                                    : 0U)
                                                   : 
                                                  ((6U 
                                                    == 
                                                    (0x0000000fU 
                                                     & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                                                    ? 
                                                   ((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                                     > vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2)
                                                     ? 1U
                                                     : 0U)
                                                    : 
                                                   (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                                    ^ vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2))))));
            }
        }
        if ((0U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
            vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res 
                = (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data)) 
                                            + (QData)((IData)(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2))));
        } else if ((1U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
            vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res 
                = (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data)) 
                                            - (QData)((IData)(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2))));
        }
    } else {
        vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out 
            = ((8U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                ? (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                   | vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2)
                : ((9U == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                    ? (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                       & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2)
                    : ((0x0aU == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                        ? (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                           << (0x0000001fU & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))
                        : ((0x0bU == (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                            ? (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                               >> (0x0000001fU & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))
                            : ((0x0cU == (0x0000000fU 
                                          & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))
                                ? VL_SHIFTRS_III(32,32,5, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2, 
                                                 (0x0000001fU 
                                                  & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))
                                : 0U)))));
        if ((8U != (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
            if ((9U != (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
                if ((0x0aU != (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
                    if ((0x0bU != (0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
                        if ((0x0cU != (0x0000000fU 
                                       & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op)))) {
                            vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res = 0ULL;
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out 
        = (IData)(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res);
    vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__wmask 
        = ((8U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
            ? ((4U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                ? 0U : ((2U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                         ? ((1U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                             ? 0U : 2U) : ((1U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                            ? 1U : 0U)))
            : ((4U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                ? 0U : ((2U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                         ? ((1U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                             ? 4U : 2U) : ((1U & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                            ? 1U : 0U))));
    if (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__mem_on) {
        Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_read_TOP____024unit(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out, vlSelfRef.__Vfunc_pRAM_read__2__Vfuncout);
        vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata 
            = vlSelfRef.__Vfunc_pRAM_read__2__Vfuncout;
        if ((0x23U == (0x0000007fU & vlSelfRef.inst))) {
            Vysyx_26020055_top___024unit____Vdpiimwrap_pRAM_write_TOP____024unit(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs2_data, (IData)(vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__wmask));
        }
    } else {
        vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata = 0U;
    }
    vlSelfRef.ysyx_26020055_top__DOT__rdata = ((8U 
                                                & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                ? (
                                                   (4U 
                                                    & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                    ? 0U
                                                    : 
                                                   ((2U 
                                                     & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                      ? 0U
                                                      : 
                                                     (((- (IData)(
                                                                  (1U 
                                                                   & (vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata 
                                                                      >> 0x0fU)))) 
                                                       << 0x00000010U) 
                                                      | (0x0000ffffU 
                                                         & vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata)))
                                                     : 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                      ? 
                                                     (((- (IData)(
                                                                  (1U 
                                                                   & (vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata 
                                                                      >> 7U)))) 
                                                       << 8U) 
                                                      | (0x000000ffU 
                                                         & vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata))
                                                      : 0U)))
                                                : (
                                                   (4U 
                                                    & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                    ? 0U
                                                    : 
                                                   ((2U 
                                                     & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                      ? vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata
                                                      : 
                                                     (0x0000ffffU 
                                                      & vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata))
                                                     : 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.ysyx_26020055_top__DOT__mem_op))
                                                      ? 
                                                     (0x000000ffU 
                                                      & vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata)
                                                      : 0U))));
}

void Vysyx_26020055_top___024root___eval_nba(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_nba\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vysyx_26020055_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

void Vysyx_26020055_top___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vysyx_26020055_top___024root___eval_phase__act(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_phase__act\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vysyx_26020055_top___024root___eval_triggers__act(vlSelf);
    Vysyx_26020055_top___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vysyx_26020055_top___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vysyx_26020055_top___024root___eval_phase__nba(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_phase__nba\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vysyx_26020055_top___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vysyx_26020055_top___024root___eval_nba(vlSelf);
        Vysyx_26020055_top___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vysyx_26020055_top___024root___eval(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vysyx_26020055_top___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_top.v", 2, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vysyx_26020055_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_top.v", 2, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vysyx_26020055_top___024root___eval_phase__act(vlSelf));
    } while (Vysyx_26020055_top___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vysyx_26020055_top___024root___eval_debug_assertions(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_debug_assertions\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
}
#endif  // VL_DEBUG
