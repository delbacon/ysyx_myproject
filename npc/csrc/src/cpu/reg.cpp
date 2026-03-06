#include "../../include/cpu.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};
//cpu.gpr存的是寄存器的值，reg_name返回的是对应寄存器的名称

static const char *reg_name(int reg_idx) {
    return regs[reg_idx];
}

void pc_get(int val){
  cpu.pc = val;
}

void dnpc_get(int val){
  cpu.dnpc = val;
}


void reg_get(int reg_idx, int val) { 
    cpu.gpr[reg_idx] = val;
}

void reg_display() {
    printf(ANSI_FMT("\t\t\tREGISTER LIST",ANSI_BG_RED));
    printf("\n");
    for(int i=0;i<32;i++){
        const char * regname =reg_name(i);
        if(strcmp(regname,"s10")==0 || strcmp(regname,"s11")==0){
          printf(ANSI_FMT("%s:", ANSI_FG_CYAN)"0x%08x	",reg_name(i),cpu.gpr[i]);
        }else{
          printf(ANSI_FMT("%s: ", ANSI_FG_CYAN)"0x%08x	",reg_name(i),cpu.gpr[i]);
        }

        if(((i+1) % 4 == 0) && i != 0) printf("\n");
    }
}

word_t reg_str2val(const char *s, bool *success) {
  
  if(strcmp(s+1,"pc")==0) return cpu.pc;
  
  for(int i=0;i<32;i++){
    //s+1以跳过开头的标识符$
    if(strcmp((s+1),reg_name(i))==0){
      *success = true;
      return cpu.gpr[i];
    }
  }
  return 0;
}


