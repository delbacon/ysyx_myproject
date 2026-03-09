/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef __CPU_ISA_H__
#define __CPU_ISA_H__

// Located at src/isa/$(GUEST_ISA)/include/isa-def.h
#include <common.h>
// The macro `__GUEST_ISA__` is defined in $(CFLAGS).
// It will be expanded as "x86" or "mips32" ...


// decode
typedef struct {
  uint32_t inst;
} ISADecodeInfo;

typedef struct {
  word_t gpr[32];
  vaddr_t pc;
  vaddr_t dnpc;
  ISADecodeInfo inst;
} CPU_state;

// monitor
extern unsigned char isa_logo[];
void init_isa();

// reg
extern CPU_state cpu;


extern "C" void pc_get_HDL(int val);
extern "C" void dnpc_get_HDL(int val);
extern "C" void reg_get_HDL(int reg_idx, int val);

const char *reg_name(int reg_idx);
void isa_reg_display();
word_t isa_reg_str2val(const char *name, bool *success);

// simulator
int isa_exec_once(struct Decode *s);
void simulator_end();
void init_sim(int argc, char** argv);

// memory

// interrupt/exception
/*
vaddr_t isa_raise_intr(word_t NO, vaddr_t epc);
#define INTR_EMPTY ((word_t)-1)
word_t isa_query_intr();
*/

// difftest


//inst
//============ inst ==============================//
extern "C" void ebreak();
extern "C" void inst_get_HDL(int inst);

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




#endif