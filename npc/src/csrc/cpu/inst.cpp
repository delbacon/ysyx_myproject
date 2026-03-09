#include <common.h>
#include <cpu/isa.h>
#include <utils.h>

void inst_get_HDL(int inst){
    cpu.inst.inst = inst;
}

// 判断是否为 JAL 指令
bool is_jal(uint32_t inst) {
    return (inst & RV_OPCODE_MASK) == RV_OP_JAL;
}

// 判断是否为 JALR 指令
bool is_jalr(uint32_t inst) {
    return ((inst & RV_OPCODE_MASK) == RV_OP_JALR) &&
           (((inst & RV_FUNCT3_MASK) >> RV_FUNCT3_SHIFT) == RV_FUNCT3_JALR);
}

// 提取 rd 寄存器（第 7-11 位）
uint32_t get_rd(uint32_t inst) {
    return (inst & RV_RD_MASK) >> RV_RD_SHIFT;
}

// 提取 JAL 指令的立即数
// 格式：imm[20|10:1|11|19:12]
int32_t get_jal_imm(uint32_t inst) {
    uint32_t imm20 = (inst >> 31) & 0x1;
    uint32_t imm10_1 = (inst >> 21) & 0x3ff;
    uint32_t imm11 = (inst >> 20) & 0x1;
    uint32_t imm19_12 = (inst >> 12) & 0xff;
    
    int32_t imm = (imm20 << 20) | (imm10_1 << 1) | (imm11 << 11) | (imm19_12 << 12);
    
    // 符号扩展
    if (imm20) {
        imm |= 0xfff00000;
    }
    
    return imm;
}

// 提取 JALR 指令的立即数
// 格式：imm[11:0]
int32_t get_jalr_imm(uint32_t inst) {
    return (int32_t)(inst & 0xfff00000) >> 20;
}

bool ebreak_flag = false;
void ebreak(){
    ebreak_flag = true;
    npc_state.state = NPC_END; 
}


