#include "../../include/common.h"
#include "../../include/cpu.h"

void inst_get(int inst){
    cpu.inst = inst;
}

void inst_print(){
    printf(ANSI_FMT("0x%08x: ",ANSI_FG_MAGENTA) ANSI_FMT("0x%08x",ANSI_FG_GREEN) "\n",cpu.pc ,cpu.inst);
}
    