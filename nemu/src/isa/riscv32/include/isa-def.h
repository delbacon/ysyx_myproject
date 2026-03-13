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

#ifndef __ISA_RISCV_H__
#define __ISA_RISCV_H__

#include <common.h>

#define MAX_CSR_IDX 4

enum { 
  //存放状态
  ADDR_MSTATUS = 0x300,//0x300
  //存放
  ADDR_MTVEC = 0x305,//0x305
  //存放触发异常的pc
  ADDR_MEPC = 0x341 ,//gpr数量+pc寄存器 //0x341
  //存放异常信息
  ADDR_MCAUSE = 0x342,//0x342
 };

enum { 
  //存放状态
  INDEX_MSTATUS=0,
  //存放
  INDEX_MTVEC,
  //存放触发异常的pc
  INDEX_MEPC,
  //存放异常信息
  INDEX_MCAUSE
 };


typedef struct {
  word_t gpr[MUXDEF(CONFIG_RVE, 16, 32)];
  vaddr_t pc;
  //谨慎改动顺序！！！通过宏定义写死了对应的位置
  word_t csr[MAX_CSR_IDX];//MEPC  MSTAUS  MCAUSE  MTVEC
} MUXDEF(CONFIG_RV64, riscv64_CPU_state, riscv32_CPU_state);

// decode
typedef struct {
  uint32_t inst;
} MUXDEF(CONFIG_RV64, riscv64_ISADecodeInfo, riscv32_ISADecodeInfo);

#define isa_mmu_check(vaddr, len, type) (MMU_DIRECT)


// intr
word_t csr_read(paddr_t addr);
void csr_write(paddr_t addr, word_t data);

#endif
