// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vysyx_26020055_top__Syms.h"


void Vysyx_26020055_top___024root__trace_chg_0_sub_0(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vysyx_26020055_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_chg_0\n"); );
    // Body
    Vysyx_26020055_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_26020055_top___024root*>(voidSelf);
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vysyx_26020055_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vysyx_26020055_top___024root__trace_chg_0_sub_0(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_chg_0_sub_0\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm),32);
        bufp->chgCData(oldp+1,(vlSelfRef.ysyx_26020055_top__DOT__exu_op),6);
        bufp->chgCData(oldp+2,(((0x00000037U == (0x0000007fU 
                                                 & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                 ? 1U : 0U)),4);
        bufp->chgCData(oldp+3,(vlSelfRef.ysyx_26020055_top__DOT__mem_op),4);
        bufp->chgIData(oldp+4,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data),32);
        bufp->chgIData(oldp+5,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs2_data),32);
        bufp->chgIData(oldp+6,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out),32);
        bufp->chgIData(oldp+7,(vlSelfRef.ysyx_26020055_top__DOT__rdata),32);
        bufp->chgBit(oldp+8,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__mem_on));
        bufp->chgCData(oldp+9,((0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op))),4);
        bufp->chgBit(oldp+10,((1U & ((IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op) 
                                     >> 5U))));
        bufp->chgIData(oldp+11,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2),32);
        bufp->chgBit(oldp+12,((0U == vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out)));
        bufp->chgBit(oldp+13,((1U & (IData)((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res 
                                             >> 0x00000020U)))));
        bufp->chgBit(oldp+14,((((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                 >> 0x0000001fU) == 
                                (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                                 >> 0x0000001fU)) & 
                               ((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                 >> 0x0000001fU) != 
                                (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out 
                                 >> 0x0000001fU)))));
        bufp->chgBit(oldp+15,((1U == ((0x00000037U 
                                       == (0x0000007fU 
                                           & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                       ? 1U : 0U))));
        bufp->chgIData(oldp+16,(((1U == ((0x00000037U 
                                          == (0x0000007fU 
                                              & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                          ? 1U : 0U))
                                  ? vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm
                                  : 0U)),32);
        bufp->chgQData(oldp+17,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res),33);
        bufp->chgIData(oldp+19,((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                                 << (0x0000001fU & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))),32);
        bufp->chgIData(oldp+20,((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                                 >> (0x0000001fU & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))),32);
        bufp->chgIData(oldp+21,(VL_SHIFTRS_III(32,32,5, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2, 
                                               (0x0000001fU 
                                                & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))),32);
        bufp->chgCData(oldp+22,(vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__wmask),8);
        bufp->chgIData(oldp+23,(vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata),32);
        bufp->chgIData(oldp+24,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[0]),32);
        bufp->chgIData(oldp+25,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[1]),32);
        bufp->chgIData(oldp+26,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[2]),32);
        bufp->chgIData(oldp+27,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[3]),32);
        bufp->chgIData(oldp+28,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[4]),32);
        bufp->chgIData(oldp+29,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[5]),32);
        bufp->chgIData(oldp+30,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[6]),32);
        bufp->chgIData(oldp+31,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[7]),32);
        bufp->chgIData(oldp+32,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[8]),32);
        bufp->chgIData(oldp+33,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[9]),32);
        bufp->chgIData(oldp+34,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[10]),32);
        bufp->chgIData(oldp+35,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[11]),32);
        bufp->chgIData(oldp+36,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[12]),32);
        bufp->chgIData(oldp+37,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[13]),32);
        bufp->chgIData(oldp+38,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[14]),32);
        bufp->chgIData(oldp+39,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[15]),32);
        bufp->chgIData(oldp+40,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[16]),32);
        bufp->chgIData(oldp+41,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[17]),32);
        bufp->chgIData(oldp+42,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[18]),32);
        bufp->chgIData(oldp+43,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[19]),32);
        bufp->chgIData(oldp+44,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[20]),32);
        bufp->chgIData(oldp+45,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[21]),32);
        bufp->chgIData(oldp+46,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[22]),32);
        bufp->chgIData(oldp+47,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[23]),32);
        bufp->chgIData(oldp+48,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[24]),32);
        bufp->chgIData(oldp+49,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[25]),32);
        bufp->chgIData(oldp+50,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[26]),32);
        bufp->chgIData(oldp+51,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[27]),32);
        bufp->chgIData(oldp+52,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[28]),32);
        bufp->chgIData(oldp+53,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[29]),32);
        bufp->chgIData(oldp+54,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[30]),32);
        bufp->chgIData(oldp+55,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[31]),32);
    }
    bufp->chgBit(oldp+56,(vlSelfRef.clk));
    bufp->chgBit(oldp+57,(vlSelfRef.rst));
    bufp->chgIData(oldp+58,(vlSelfRef.pc),32);
    bufp->chgCData(oldp+59,(vlSelfRef.jmp_op),4);
    bufp->chgIData(oldp+60,(vlSelfRef.inst),32);
    bufp->chgCData(oldp+61,((0x0000001fU & (vlSelfRef.inst 
                                            >> 0x0000000fU))),5);
    bufp->chgCData(oldp+62,((0x0000001fU & (vlSelfRef.inst 
                                            >> 0x00000014U))),5);
    bufp->chgCData(oldp+63,((0x0000001fU & (vlSelfRef.inst 
                                            >> 7U))),5);
    bufp->chgBit(oldp+64,(((0x33U == (0x0000007fU & vlSelfRef.inst)) 
                           | ((0x3bU == (0x0000007fU 
                                         & vlSelfRef.inst)) 
                              | ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_5) 
                                 | ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_2) 
                                    | ((0x6fU == (0x0000007fU 
                                                  & vlSelfRef.inst)) 
                                       | (0x63U == 
                                          (0x0000007fU 
                                           & vlSelfRef.inst)))))))));
    bufp->chgBit(oldp+65,((3U == (0x0000007fU & vlSelfRef.inst))));
    bufp->chgBit(oldp+66,((0x23U == (0x0000007fU & vlSelfRef.inst))));
    bufp->chgCData(oldp+67,(((0x00100073U == vlSelfRef.inst)
                              ? 2U : 0U)),4);
    bufp->chgIData(oldp+68,(((2U == (IData)(vlSelfRef.jmp_op))
                              ? (0xfffffffeU & (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                                + vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm))
                              : 0U)),32);
    bufp->chgIData(oldp+69,(((2U == (IData)(vlSelfRef.jmp_op))
                              ? ((2U == (IData)(vlSelfRef.jmp_op))
                                  ? ((IData)(4U) + vlSelfRef.pc)
                                  : 0U) : ((1U == (
                                                   (0x00000037U 
                                                    == 
                                                    (0x0000007fU 
                                                     & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                    ? 1U
                                                    : 0U))
                                            ? ((1U 
                                                == 
                                                ((0x00000037U 
                                                  == 
                                                  (0x0000007fU 
                                                   & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                  ? 1U
                                                  : 0U))
                                                ? vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm
                                                : 0U)
                                            : ((IData)(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__mem_on)
                                                ? vlSelfRef.ysyx_26020055_top__DOT__rdata
                                                : vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out)))),32);
    bufp->chgBit(oldp+70,((2U == (IData)(vlSelfRef.jmp_op))));
    bufp->chgIData(oldp+71,(((2U == (IData)(vlSelfRef.jmp_op))
                              ? ((IData)(4U) + vlSelfRef.pc)
                              : 0U)),32);
    bufp->chgCData(oldp+72,((0x0000007fU & vlSelfRef.inst)),7);
    bufp->chgCData(oldp+73,((7U & (vlSelfRef.inst >> 0x0000000cU))),3);
    bufp->chgCData(oldp+74,((vlSelfRef.inst >> 0x00000019U)),7);
    bufp->chgIData(oldp+75,(((2U == (IData)(vlSelfRef.jmp_op))
                              ? ((2U == (IData)(vlSelfRef.jmp_op))
                                  ? (0xfffffffeU & 
                                     (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                      + vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm))
                                  : 0U) : ((IData)(4U) 
                                           + vlSelfRef.pc))),32);
}

void Vysyx_26020055_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_cleanup\n"); );
    // Body
    Vysyx_26020055_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_26020055_top___024root*>(voidSelf);
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
