#include <trace/dtrace.h>
#include <utils.h>

#ifdef CONFIG_DTRACE
void dtrace_read(vaddr_t addr, word_t ret, IOMap *map){
    if(addr >=CONFIG_DTRACE_START && addr < CONFIG_DTRACE_END){
      word_t tmp_array[4];
      for(int i=0;i<4;i++){
        tmp_array[i] = (ret & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
      }
      log_write(ANSI_FMT("[DEV]",ANSI_FG_WHITE) 
                ANSI_FMT("[READ ] ",ANSI_FG_RED) 
                ANSI_FMT(FMT_PADDR": ",ANSI_FG_MAGENTA), addr);
      for(int i=0;i<4;i++){
        log_write("%02x ", tmp_array[i] );
      }
      log_write(ANSI_FMT("[%s]",ANSI_FG_GREEN), map->name);
      log_write("\n");
  }
}

void dtrace_write(vaddr_t addr, int len , word_t data, IOMap *map){
    if(addr >=CONFIG_DTRACE_START && addr < CONFIG_DTRACE_END){
      word_t tmp_array[4];
      for(int i=0;i<4;i++){
        tmp_array[i] = (data & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
      }
      log_write(ANSI_FMT("[DEV]",ANSI_FG_WHITE) 
                ANSI_FMT("[WRITE] ",ANSI_FG_BLUE) 
                ANSI_FMT(FMT_PADDR": ",ANSI_FG_CYAN), addr);
      for(int i=0;i<4;i++){
        log_write("%02x ", tmp_array[i] );
      }
      log_write(ANSI_FMT("[%s]",ANSI_FG_GREEN), map->name);
      log_write("wmask:%x", len);
      log_write("\n");
    }
}
#endif
