#include <cpu/cpu.h>
#include <utils.h>


void mtrace_write(paddr_t addr, int len, word_t data){
    if(addr >=CONFIG_MTRACE_START && addr < CONFIG_MTRACE_END){
       word_t tmp_array[8];
       for(int i=0;i<sizeof(word_t);i++){
         tmp_array[i] = (data & (~0xffu >> (8 * i)) ) >> (8 * (3-i));
       }
       log_write(ANSI_FMT("[MEM]",ANSI_FG_GREEN) 
                 ANSI_FMT("[WRITE] ",ANSI_FG_BLUE) 
                 ANSI_FMT(FMT_PADDR": ",ANSI_FG_CYAN), addr);
       for(int i=0;i<4;i++){
         log_write("%02x ", tmp_array[i] );
       }
         log_write("  wmask:%x ", len );
       log_write("\n");
    }
}

void mtrace_read(paddr_t addr, int len, word_t data){
    if(addr >=CONFIG_MTRACE_START && addr < CONFIG_MTRACE_END){
        word_t tmp_array[4];
        for(int i=0;i<4;i++){
            tmp_array[i] = (data & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
        }
        log_write(ANSI_FMT("[MEM]",ANSI_FG_GREEN) 
                    ANSI_FMT("[READ ] ",ANSI_FG_RED) 
                    ANSI_FMT(FMT_PADDR": ",ANSI_FG_MAGENTA), addr);
        for(int i=0;i<4;i++){
            log_write("%02x ", tmp_array[i] );
        }
        log_write("\n");
    }
}
