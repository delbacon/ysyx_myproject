#ifndef __CPU_H__
#define __CPU_H__ 

// include/cpu.h

#include "common.h"
#include "utils.h"
#include <stdint.h>

// 定义可能的运行状态
enum{
    STATE_START,STATE_EBREAK,STATE_ABORT,STATE_RUNNING,STATE_STOP,STATE_END,
};


// 定义结构体
typedef struct {
    uint32_t *pROM;
    uint32_t *pRAM;
    word_t pc;
    word_t dnpc;
    uint32_t inst;
    uint32_t gpr[32];
    int sim_time;
    int state;
} CPU_T;

// 声明全局变量（extern 表示“在别处定义”）
extern CPU_T cpu;
//============ inst ==============================//
// RISC-V 指令 opcode 定义
#define RV_OP_JAL  0x6f
#define RV_OP_JALR 0x67

// RISC-V 指令 funct3 定义
#define RV_FUNCT3_JALR 0x0

// 指令掩码
#define RV_OPCODE_MASK 0x7f
#define RV_RD_MASK 0xf80
#define RV_RD_SHIFT 7
#define RV_RS1_MASK 0xf8000
#define RV_RS1_SHIFT 15
#define RS2_MASK 0x1f00000
#define RS2_SHIFT 20
#define RV_FUNCT3_MASK 0x7000
#define RV_FUNCT3_SHIFT 12

// 判断函数
bool is_jal(uint32_t inst);
bool is_jalr(uint32_t inst);

// 提取函数
uint32_t get_rd(uint32_t inst);
int32_t get_jal_imm(uint32_t inst);
int32_t get_jalr_imm(uint32_t inst);

extern "C" void inst_get(int inst);


//================================================//
const char *reg_name(int reg_idx);


extern "C" void pc_get(int val);

extern "C" void dnpc_get(int val);

extern "C" void reg_get(int reg_idx, int val);

void reg_display() ;

word_t reg_str2val(const char *s, bool *success);





#endif // __CPU_H__
