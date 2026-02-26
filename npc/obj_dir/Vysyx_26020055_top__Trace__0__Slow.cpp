// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vysyx_26020055_top__Syms.h"


VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_init_sub__TOP__0(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_init_sub__TOP__0\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+57,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+59,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+60,0,"jmp_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+61,0,"inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("ysyx_26020055_top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+57,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+59,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+60,0,"jmp_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+61,0,"inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+62,0,"rs1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+63,0,"rs2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+64,0,"rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+1,0,"imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+65,0,"reg_wr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"mem_rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"mem_wr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"exu_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+3,0,"uncal_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+4,0,"mem_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+68,0,"sys_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+69,0,"pc_jmp_target",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+70,0,"reg_wr_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"rs1_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"rs2_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+71,0,"jmp_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"raddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+8,0,"rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("EXU", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+5,0,"rs1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"rs2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+1,0,"imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"exu_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+60,0,"jmp_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"uncal_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+68,0,"sys_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+59,0,"pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+8,0,"rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+9,0,"mem_on",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+71,0,"jmp_taken",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+69,0,"pc_jmp_target",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+70,0,"reg_wr_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"mem_rd_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"mem_wr_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"alu_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+11,0,"exu_src",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"src1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"src2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+13,0,"alu_zero",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"alu_cout",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+15,0,"alu_overflow",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"alu_out",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+72,0,"rd_jmp_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+16,0,"uncal_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"uncal_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("alu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+5,0,"a",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"b",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+7,0,"y",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+13,0,"zero",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+15,0,"overflow",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+18,0,"res",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 32,0);
    tracep->declBus(c+20,0,"shl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+21,0,"shr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+22,0,"sar",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("IDU", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+61,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+62,0,"rs1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+63,0,"rs2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+64,0,"rd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+1,0,"imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+65,0,"reg_wr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"mem_rd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"mem_wr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"exu_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+60,0,"jmp_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+4,0,"mem_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"uncal_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+68,0,"sys_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+73,0,"opcode",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+74,0,"funct3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+75,0,"funct7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->pushPrefix("IFU", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+59,0,"pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+61,0,"inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("LSU", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+7,0,"raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"wnum",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+9,0,"valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+8,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"wmask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+24,0,"pmem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("WBU", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+57,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+62,0,"rs1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+63,0,"rs2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+64,0,"rd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+70,0,"wr_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+65,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+71,0,"jmp_taken",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+69,0,"pc_jmp_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"rs1_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"rs2_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+59,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+76,0,"next_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("u_RegisterFile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+77,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+78,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+57,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+70,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+64,0,"waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+62,0,"raddr1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+63,0,"raddr2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+65,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"rdata1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"rdata2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("rf", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+25+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_init_top(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_init_top\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vysyx_26020055_top___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vysyx_26020055_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vysyx_26020055_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_register(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_register\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vysyx_26020055_top___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vysyx_26020055_top___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vysyx_26020055_top___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vysyx_26020055_top___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_const_0_sub_0(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_const_0\n"); );
    // Body
    Vysyx_26020055_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_26020055_top___024root*>(voidSelf);
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vysyx_26020055_top___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_const_0_sub_0(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_const_0_sub_0\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+77,(5U),32);
    bufp->fullIData(oldp+78,(0x00000020U),32);
}

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_full_0_sub_0(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_full_0\n"); );
    // Body
    Vysyx_26020055_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_26020055_top___024root*>(voidSelf);
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vysyx_26020055_top___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vysyx_26020055_top___024root__trace_full_0_sub_0(Vysyx_26020055_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_26020055_top___024root__trace_full_0_sub_0\n"); );
    Vysyx_26020055_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+1,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm),32);
    bufp->fullCData(oldp+2,(vlSelfRef.ysyx_26020055_top__DOT__exu_op),6);
    bufp->fullCData(oldp+3,(((0x00000037U == (0x0000007fU 
                                              & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                              ? 1U : 0U)),4);
    bufp->fullCData(oldp+4,(vlSelfRef.ysyx_26020055_top__DOT__mem_op),4);
    bufp->fullIData(oldp+5,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data),32);
    bufp->fullIData(oldp+6,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs2_data),32);
    bufp->fullIData(oldp+7,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out),32);
    bufp->fullIData(oldp+8,(vlSelfRef.ysyx_26020055_top__DOT__rdata),32);
    bufp->fullBit(oldp+9,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__mem_on));
    bufp->fullCData(oldp+10,((0x0000000fU & (IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op))),4);
    bufp->fullBit(oldp+11,((1U & ((IData)(vlSelfRef.ysyx_26020055_top__DOT__exu_op) 
                                  >> 5U))));
    bufp->fullIData(oldp+12,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2),32);
    bufp->fullBit(oldp+13,((0U == vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out)));
    bufp->fullBit(oldp+14,((1U & (IData)((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res 
                                          >> 0x00000020U)))));
    bufp->fullBit(oldp+15,((((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                              >> 0x0000001fU) == (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                                                  >> 0x0000001fU)) 
                            & ((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                >> 0x0000001fU) != 
                               (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu_out 
                                >> 0x0000001fU)))));
    bufp->fullBit(oldp+16,((1U == ((0x00000037U == 
                                    (0x0000007fU & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                    ? 1U : 0U))));
    bufp->fullIData(oldp+17,(((1U == ((0x00000037U 
                                       == (0x0000007fU 
                                           & vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                       ? 1U : 0U)) ? vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm
                               : 0U)),32);
    bufp->fullQData(oldp+18,(vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__alu__DOT__res),33);
    bufp->fullIData(oldp+20,((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                              << (0x0000001fU & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))),32);
    bufp->fullIData(oldp+21,((vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2 
                              >> (0x0000001fU & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))),32);
    bufp->fullIData(oldp+22,(VL_SHIFTRS_III(32,32,5, vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__src2, 
                                            (0x0000001fU 
                                             & vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data))),32);
    bufp->fullCData(oldp+23,(vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__wmask),8);
    bufp->fullIData(oldp+24,(vlSelfRef.ysyx_26020055_top__DOT__LSU__DOT__pmem_rdata),32);
    bufp->fullIData(oldp+25,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[0]),32);
    bufp->fullIData(oldp+26,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[1]),32);
    bufp->fullIData(oldp+27,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[2]),32);
    bufp->fullIData(oldp+28,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[3]),32);
    bufp->fullIData(oldp+29,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[4]),32);
    bufp->fullIData(oldp+30,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[5]),32);
    bufp->fullIData(oldp+31,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[6]),32);
    bufp->fullIData(oldp+32,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[7]),32);
    bufp->fullIData(oldp+33,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[8]),32);
    bufp->fullIData(oldp+34,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[9]),32);
    bufp->fullIData(oldp+35,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[10]),32);
    bufp->fullIData(oldp+36,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[11]),32);
    bufp->fullIData(oldp+37,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[12]),32);
    bufp->fullIData(oldp+38,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[13]),32);
    bufp->fullIData(oldp+39,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[14]),32);
    bufp->fullIData(oldp+40,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[15]),32);
    bufp->fullIData(oldp+41,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[16]),32);
    bufp->fullIData(oldp+42,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[17]),32);
    bufp->fullIData(oldp+43,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[18]),32);
    bufp->fullIData(oldp+44,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[19]),32);
    bufp->fullIData(oldp+45,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[20]),32);
    bufp->fullIData(oldp+46,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[21]),32);
    bufp->fullIData(oldp+47,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[22]),32);
    bufp->fullIData(oldp+48,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[23]),32);
    bufp->fullIData(oldp+49,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[24]),32);
    bufp->fullIData(oldp+50,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[25]),32);
    bufp->fullIData(oldp+51,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[26]),32);
    bufp->fullIData(oldp+52,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[27]),32);
    bufp->fullIData(oldp+53,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[28]),32);
    bufp->fullIData(oldp+54,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[29]),32);
    bufp->fullIData(oldp+55,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[30]),32);
    bufp->fullIData(oldp+56,(vlSelfRef.ysyx_26020055_top__DOT__WBU__DOT__u_RegisterFile__DOT__rf[31]),32);
    bufp->fullBit(oldp+57,(vlSelfRef.clk));
    bufp->fullBit(oldp+58,(vlSelfRef.rst));
    bufp->fullIData(oldp+59,(vlSelfRef.pc),32);
    bufp->fullCData(oldp+60,(vlSelfRef.jmp_op),4);
    bufp->fullIData(oldp+61,(vlSelfRef.inst),32);
    bufp->fullCData(oldp+62,((0x0000001fU & (vlSelfRef.inst 
                                             >> 0x0000000fU))),5);
    bufp->fullCData(oldp+63,((0x0000001fU & (vlSelfRef.inst 
                                             >> 0x00000014U))),5);
    bufp->fullCData(oldp+64,((0x0000001fU & (vlSelfRef.inst 
                                             >> 7U))),5);
    bufp->fullBit(oldp+65,(((0x33U == (0x0000007fU 
                                       & vlSelfRef.inst)) 
                            | ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_3) 
                               | ((IData)(vlSelfRef.ysyx_26020055_top__DOT__IDU__DOT____VdfgRegularize_h61fff987_0_1) 
                                  | (0x6fU == (0x0000007fU 
                                               & vlSelfRef.inst)))))));
    bufp->fullBit(oldp+66,((3U == (0x0000007fU & vlSelfRef.inst))));
    bufp->fullBit(oldp+67,((0x23U == (0x0000007fU & vlSelfRef.inst))));
    bufp->fullCData(oldp+68,(((0x00100073U == vlSelfRef.inst)
                               ? 2U : 0U)),4);
    bufp->fullIData(oldp+69,(((2U == (IData)(vlSelfRef.jmp_op))
                               ? (0xfffffffeU & (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                                 + vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm))
                               : 0U)),32);
    bufp->fullIData(oldp+70,(((2U == (IData)(vlSelfRef.jmp_op))
                               ? ((2U == (IData)(vlSelfRef.jmp_op))
                                   ? ((IData)(4U) + vlSelfRef.pc)
                                   : 0U) : ((1U == 
                                             ((0x00000037U 
                                               == (0x0000007fU 
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
    bufp->fullBit(oldp+71,((2U == (IData)(vlSelfRef.jmp_op))));
    bufp->fullIData(oldp+72,(((2U == (IData)(vlSelfRef.jmp_op))
                               ? ((IData)(4U) + vlSelfRef.pc)
                               : 0U)),32);
    bufp->fullCData(oldp+73,((0x0000007fU & vlSelfRef.inst)),7);
    bufp->fullCData(oldp+74,((7U & (vlSelfRef.inst 
                                    >> 0x0000000cU))),3);
    bufp->fullCData(oldp+75,((vlSelfRef.inst >> 0x00000019U)),7);
    bufp->fullIData(oldp+76,(((2U == (IData)(vlSelfRef.jmp_op))
                               ? ((2U == (IData)(vlSelfRef.jmp_op))
                                   ? (0xfffffffeU & 
                                      (vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__rs1_data 
                                       + vlSelfRef.ysyx_26020055_top__DOT__EXU__DOT__imm))
                                   : 0U) : ((IData)(4U) 
                                            + vlSelfRef.pc))),32);
}
