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

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write

enum {
  TYPE_3R, TYPE_2RI12, TYPE_1RI20,
  TYPE_N, // none
};

#define src1R()  do { *src1 = R(rj); } while (0)
#define src2R()  do { *src2 = R(rk); } while (0)
#define simm12() do { *imm = SEXT(BITS(i, 21, 10), 12); } while (0)//SEXT宏用于符号位扩展
#define simm20() do { *imm = SEXT(BITS(i, 24, 5), 20) << 12; } while (0)


//操作数解码
static void decode_operand(Decode *s, int *rd_, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;

  //从inst中提取寄存器，立即数等各个部分（这里funct3和opcode被预处理去掉了）
  //----------------------------------//
  //rs1,对应bit位inst[9:5]
  int rj = BITS(i, 9, 5);
  //rs2,对应bit位
  int rk = BITS(i, 19, 15);
  //rd,对应bit位inst[4:0]
  *rd_ = BITS(i, 4, 0);//BITS宏用于位抽取
  //src1R()用于将寄存器的读取结果暂存到相应的操作数变量src1中
  switch (type) {
    //R-type
    case TYPE_3R: src2R(); src1R(); srcRd(); break;
    //I-type
    case TYPE_2RI12: simm12(); src1R(); break;
    //U-type
    case TYPE_1RI20: simm20(); src1R(); break;
    case TYPE_N: break;
    default: panic("Unsupport type = %d", type);
  }
}

static int decode_exec(Decode *s) {
  s->dnpc = s->snpc;

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
  //lui
  INSTPAT("???????????????????? ????? 0110111"    , lui      , 1RI20 , R(rd) = (imm << 12));
  //auipc
  INSTPAT("0001110 ????? ????? ????? ????? ?????" , pcaddu12i, 1RI20 , R(rd) = s->pc + imm);
  //jal 将当前pc+4保存到rd,并且跳转到pc+signoffset(imm)
  INSTPAT("???????????????????? ????? 1101111"    , jal      , 1RI20 , R(rd) = s->dnpc, s->dnpc = s->pc + imm);
  //lw
  INSTPAT("0010100010 ???????????? ????? ?????"   , ld.w     , 2RI12 , R(rd) = Mr(src1 + imm, 4));
  //sw
  INSTPAT("0010100110 ???????????? ????? ?????"   , st.w     , 2RI12 , Mw(src1 + imm, 4, R(rd)));

  //addi/li
  //INSTPAT("???????????? ????? 000 ????? 0010011"  , addi     , 2RI12 , R(rd) = src1 + imm);

  //break
  INSTPAT("0000 0000 0010 10100 ????? ????? ?????", break    , N     , NEMUTRAP(s->pc, R(4))); // R(4) is $a0
  //inv
  INSTPAT("????????????????? ????? ????? ?????"   , inv      , N     , INV(s->pc));
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
