// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_26020055_top.h for the primary calling header

#include "Vysyx_26020055_top__pch.h"

VL_ATTR_COLD void Vysyx_26020055_top___024root___eval_static(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_static\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vysyx_26020055_top___024root___eval_initial(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_initial\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vysyx_26020055_top___024root___eval_final(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_final\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_26020055_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vysyx_26020055_top___024root___eval_phase__stl(Vysyx_26020055_top___024root* vlSelf);

VL_ATTR_COLD void Vysyx_26020055_top___024root___eval_settle(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_settle\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vysyx_26020055_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/delbacon/ysyx-workbench/npc/vsrc/ysyx_26020055_top.v", 2, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vysyx_26020055_top___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vysyx_26020055_top___024root___eval_triggers__stl(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_triggers__stl\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_26020055_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vysyx_26020055_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_26020055_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vysyx_26020055_top___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vysyx_26020055_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___trigger_anySet__stl\n"); );
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

void Vysyx_26020055_top___024unit____Vdpiimwrap_pROM_read_TOP____024unit(IData/*31:0*/ vraddr, IData/*31:0*/ &pROM_read__Vfuncrtn);
void Vysyx_26020055_top___024unit____Vdpiimwrap_ebreak_TOP____024unit();
void Vysyx_26020055_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ vraddr, IData/*31:0*/ &pmem_read__Vfuncrtn);
void Vysyx_26020055_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ vwaddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

VL_ATTR_COLD void Vysyx_26020055_top___024root___stl_sequent__TOP__0(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___stl_sequent__TOP__0\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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
        Vysyx_26020055_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out, vlSelfRef.__Vfunc_pmem_read__2__Vfuncout);
        vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata 
            = vlSelfRef.__Vfunc_pmem_read__2__Vfuncout;
        if ((0x23U == (0x0000007fU & vlSelfRef.inst))) {
            Vysyx_26020055_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs2_data, (IData)(vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__wmask));
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

VL_ATTR_COLD void Vysyx_26020055_top___024root____Vm_traceActivitySetAll(Vysyx_26020055_top___024root* vlSelf);

VL_ATTR_COLD void Vysyx_26020055_top___024root___eval_stl(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_stl\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vysyx_26020055_top___024root___stl_sequent__TOP__0(vlSelf);
        Vysyx_26020055_top___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vysyx_26020055_top___024root___eval_phase__stl(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___eval_phase__stl\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vysyx_26020055_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vysyx_26020055_top___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vysyx_26020055_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vysyx_26020055_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_26020055_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vysyx_26020055_top___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vysyx_26020055_top___024root____Vm_traceActivitySetAll(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root____Vm_traceActivitySetAll\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vysyx_26020055_top___024root___ctor_var_reset(Vysyx_26020055_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root___ctor_var_reset\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4211327832146562899ull);
    vlSelf->jmp_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9665227910938620571ull);
    vlSelf->inst = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9812503827101699671ull);
    vlSelf->ysyx_26020055_top__DOT__exu_op = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 17360470747500733159ull);
    vlSelf->ysyx_26020055_top__DOT__mem_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4541545987858893ull);
    vlSelf->ysyx_26020055_top__DOT__rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12044269421977864567ull);
    vlSelf->ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_2 = 0;
    vlSelf->ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_5 = 0;
    vlSelf->ysyx_26020055_top__DOT__EXU__DOT__rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12256637911115429599ull);
    vlSelf->ysyx_26020055_top__DOT__EXU__DOT__rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14306086084910650115ull);
    vlSelf->ysyx_26020055_top__DOT__EXU__DOT__imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10993773100900230847ull);
    vlSelf->ysyx_26020055_top__DOT__EXU__DOT__mem_on = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9472789647932811861ull);
    vlSelf->ysyx_26020055_top__DOT__EXU__DOT__src2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11552323649725797152ull);
    vlSelf->ysyx_26020055_top__DOT__EXU__DOT__alu_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2104596859487953261ull);
    vlSelf->ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 3188922138492630469ull);
    vlSelf->ysyx_26020055_top__DOT__LSU__DOT__wmask = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11840092452638666416ull);
    vlSelf->ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2238558223678868536ull);
    vlSelf->ysyx_26020055_top__DOT__WBU__DOT__next_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14956962441824609790ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8600487574280312091ull);
    }
    vlSelf->__Vfunc_pROM_read__0__Vfuncout = 0;
    vlSelf->__Vfunc_pmem_read__2__Vfuncout = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
