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

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>
#include <trace/ftrace.h>

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write

sword_t min_val = MUXDEF(CONFIG_ISA64, INT64_MIN, INT32_MIN);

//enum存储riscv六种指令类型
enum {
  TYPE_R, TYPE_I, TYPE_S,TYPE_B, TYPE_U, TYPE_J,
  TYPE_N, // none
};

//define读取立即数的值,并将相应的寄存器值保存在src1和src2中
//---------------------------------------------//
#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)

#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immB() do { *imm = ((SEXT(BITS(i, 31, 31), 1) << 12) | (BITS(i, 7, 7) << 11) | (BITS(i, 30, 25) << 5) | (BITS(i, 11, 8) << 1) | 0 ); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immJ() do { *imm = (((SEXT(BITS(i, 31, 31), 1) << 20) | (BITS(i, 19, 12) << 12) | (BITS(i, 20, 20) << 11) | (BITS(i, 30, 21) << 1) | 0)) ; } while(0)

//---------------------------------------------//


static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;
  //因为RISCV指令集rs1,rs2和rd位置确定，所以先统一读取，再通过switch判断所属指令类型，然后对症下药
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_R: src1R(); src2R();         break;
    case TYPE_I: src1R();          immI(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_B: src1R(); src2R(); immB(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_J:                   immJ(); break;
    case TYPE_N: break;
    default: panic("unsupported type = %d", type);
  }
}

static int decode_exec(Decode *s) {
  s->dnpc = s->snpc;
  word_t inst = s->isa.inst;

#define INSTPAT_INST(s) ((s)->isa.inst)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  int rd = 0; \
  word_t src1 = 0, src2 = 0, imm = 0; \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}
//通过opcode的格式进行匹配，0匹配0,1匹配1,？匹配0和1
//INSTPAT(模式字符串, 指令名称, 指令类型, 指令执行操作)
//指令名称作为注释，指令类型用于后续译码
  INSTPAT_START();
  INSTPAT("??????? ????? ????? ??? ????? 01101 11", lui    , U, R(rd) = imm);
  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = s->pc + imm);
  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J, R(rd) = s->snpc; s->dnpc = s->pc + imm;
                                                                  IFDEF(CONFIG_FTRACE, if(rd == 1) ftrace_call(s->pc, s->dnpc); )
                                                                );
  INSTPAT("??????? ????? ????? 000 ????? 11001 11", jalr   , I, R(rd) = s->snpc; s->dnpc = (src1 + imm) & ~1;
                                                                  IFDEF(CONFIG_FTRACE,{
                                                                  if(s->isa.inst == 0x00008067) ftrace_ret(s->pc);
                                                                  else if (rd == 1) ftrace_call(s->pc, s->dnpc);
                                                                  else if (rd == 0 && imm == 0) ftrace_call(s->pc, s->dnpc); 
                                                                  // jr rs1 -> jalr x0, 0(rs1), which may be other control flow e.g. 'goto','for'
                                                                });
                                                                );

  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B, if(src1==src2){s->dnpc = s->pc + imm;});//also beqz
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B, if(src1!=src2){s->dnpc = s->pc + imm;});
  INSTPAT("??????? ????? ????? 100 ????? 11000 11", blt    , B, if((sword_t)src1< (sword_t)src2){s->dnpc = s->pc + imm;});
  INSTPAT("??????? ????? ????? 101 ????? 11000 11", bge    , B, if((sword_t)src1>=(sword_t)src2){s->dnpc = s->pc + imm;});
  INSTPAT("??????? ????? ????? 110 ????? 11000 11", bltu   , B, if(src1< src2){s->dnpc = s->pc + imm;});
  INSTPAT("??????? ????? ????? 111 ????? 11000 11", bgeu   , B, if(src1>=src2){s->dnpc = s->pc + imm;});

  INSTPAT("??????? ????? ????? 000 ????? 00000 11", lb     , I, R(rd) = SEXT(Mr(src1 + imm, 1),  8));
  INSTPAT("??????? ????? ????? 001 ????? 00000 11", lh     , I, R(rd) = SEXT(Mr(src1 + imm, 2), 16));
  INSTPAT("??????? ????? ????? 010 ????? 00000 11", lw     , I, R(rd) = Mr(src1 + imm, 4));
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = Mr(src1 + imm, 1));
  INSTPAT("??????? ????? ????? 101 ????? 00000 11", lhu    , I, R(rd) = Mr(src1 + imm, 2));


  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, Mw(src1 + imm, 1, src2));
  INSTPAT("??????? ????? ????? 001 ????? 01000 11", sh     , S, Mw(src1 + imm, 2, src2));
  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, Mw(src1 + imm, 4, src2));


  INSTPAT("??????? ????? ????? 000 ????? 00100 11", addi   , I, R(rd) = src1 + imm);
  INSTPAT("??????? ????? ????? 010 ????? 00100 11", slti   , I, if((sword_t)src1 < (sword_t)imm) {R(rd) = 1;} \
                                                                else {R(rd) = 0;});
  //如果rs1==0,则rd=1（seqz通过和1比较实现）,如果rs<imm,则rd=1
  INSTPAT("??????? ????? ????? 011 ????? 00100 11", sltiu  , I, if(src1 < imm) {R(rd) = 1;} \
                                                                else {R(rd) = 0;});//also seqz
  INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd) = src1 ^ imm);     
  INSTPAT("??????? ????? ????? 110 ????? 00100 11", ori    , I, R(rd) = src1 | imm);                                                       
  INSTPAT("??????? ????? ????? 111 ????? 00100 11", andi   , I, R(rd) = src1 & imm);
  INSTPAT("0000000 ????? ????? 001 ????? 00100 11", slli   , I, R(rd) = src1 << BITS(inst, 24, 20));
  INSTPAT("0000000 ????? ????? 101 ????? 00100 11", srli   , I, R(rd) = src1 >> BITS(inst, 24, 20));
  INSTPAT("0100000 ????? ????? 101 ????? 00100 11", srai   , I, R(rd) = (sword_t)src1 >> BITS(inst, 24, 20));//a=arch..算数右移，gcc默认带符号为算数右移  

  INSTPAT("0000000 ????? ????? 000 ????? 01100 11", add    , R, R(rd) = src1 + src2);
  INSTPAT("0100000 ????? ????? 000 ????? 01100 11", sub    , R, R(rd) = src1 - src2);
  INSTPAT("0000000 ????? ????? 001 ????? 01100 11", sll    , R, R(rd) = src1 << BITS(src2, 4, 0));
  INSTPAT("0000000 ????? ????? 010 ????? 01100 11", slt    , R, if((sword_t)src1 < (sword_t)src2) {R(rd) = 1;}\
                                                                else {R(rd) = 0;} );
  INSTPAT("0000000 ????? ????? 011 ????? 01100 11", sltu   , R, if((src1 < src2)) {R(rd) = 1;}\
                                                                else {R(rd) = 0;} );//要求为src1=x0时，src2 != 0则rd=1，但是实际不用额外加逻辑去判断
  INSTPAT("0000000 ????? ????? 100 ????? 01100 11", xor    , R, R(rd) = src1 ^ src2);
  INSTPAT("0000000 ????? ????? 101 ????? 01100 11", srl    , R, R(rd) = src1 >> BITS(src2, 4, 0));
  INSTPAT("0100000 ????? ????? 101 ????? 01100 11", sra    , R, R(rd) = (sword_t)src1 >> BITS(src2, 4, 0));
  INSTPAT("0000000 ????? ????? 110 ????? 01100 11", or     , R, R(rd) = src1 | src2);
  INSTPAT("0000000 ????? ????? 111 ????? 01100 11", and    , R, R(rd) = src1 & src2);

  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10))); // R(10) is $a0

  //M extension
  //attention!!! 类型没有用宏定义实现，更换环境的话可能要手动改
  //(uint64_t)(int32_t)无符号32位不能直接扩展为64位，要先扩展位有符号32位,再扩展为无符号64位
  INSTPAT("0000001 ????? ????? 000 ????? 01100 11", mul    , R, R(rd) = (sword_t)src1 * (sword_t)src2);
  INSTPAT("0000001 ????? ????? 001 ????? 01100 11", mulh   , R, R(rd) = BITS((int64_t)(int32_t)src1 * (sword_t)src2 , 63, 32) );
  INSTPAT("0000001 ????? ????? 010 ????? 01100 11", mulhsu , R, R(rd) = BITS((int64_t)(int32_t)src1 * src2 , 63, 32) );
  INSTPAT("0000001 ????? ????? 011 ????? 01100 11", mulhu  , R, R(rd) = BITS((int64_t)src1 * src2 , 63, 32)  );
  INSTPAT("0000001 ????? ????? 100 ????? 01100 11", div    , R, if(src2==0) {R(rd)=-1;} \
                                                                else if(src1==min_val && src2==-1) {R(rd)=min_val;}
                                                                else {R(rd)=(sword_t)src1 / (sword_t)src2;});
  INSTPAT("0000001 ????? ????? 101 ????? 01100 11", divu   , R, if(src2==0) {R(rd)=-1;} \
                                                                else {R(rd)=src1 / src2;});                                                            
  INSTPAT("0000001 ????? ????? 110 ????? 01100 11", rem    , R, if(src2==0) {R(rd)=src1;} \
                                                                else if(src1==min_val && src2==-1) {R(rd)=0;}
                                                                else {R(rd)=(sword_t)src1 % (sword_t)src2;});
  INSTPAT("0000001 ????? ????? 111 ????? 01100 11", remu   , R, if(src2==0) {R(rd)=src1;} \
                                                                else {R(rd)=src1 % src2;});                                                            

  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc));
  INSTPAT_END();

  R(0) = 0; // reset $zero to 0

  return 0;
}
//作用是从内存中取出一条指令，并且让snpc指向下一条指令的位置
int isa_exec_once(Decode *s) {
  s->isa.inst = inst_fetch(&s->snpc, 4);

  //进入译码
  return decode_exec(s);
}
