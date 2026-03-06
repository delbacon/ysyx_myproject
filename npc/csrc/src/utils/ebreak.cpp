#include "../../include/utils.h"
#include "../../include/memory.h"
#include "../../include/cpu.h"
void ebreak()
{
	cpu.state = STATE_EBREAK ;
}

int ebreak_success_print()
{
    pmem_free();
    reg_display();
    
    if(cpu.state == STATE_EBREAK){
      printf("\033[1;30;32mHIT GOOD TRAP\033[0m\n");
      return 0;
    }else if(cpu.state == STATE_END){
      printf(ANSI_FMT("QUIT SUCCESSFULY", ANSI_FG_CYAN));
      printf("\n");
      return -1;
    }else {
      printf("\033[1;30;31mHIT BAD TRAP\033[0m\n");
      return -1;
    }
}