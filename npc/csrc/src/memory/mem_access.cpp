#include "../../include/memory.h"
#include "../../include/device.h"
#include "../../include/cpu.h"

//#define PROM_READ

//pcROM
//===================================================//
int pROM_read(int vraddr) {
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  uint32_t raddr = 0;
  if(vraddr >= 0x80000000) raddr = vraddr - 0x80000000;

#ifdef PROM_READ
  return cpu.pROM[(raddr>>2)];
#else
  return cpu.pROM[(raddr>>2)];
#endif
}
//===================================================//



//RAM
//===================================================//
int pRAM_read(int vraddr) {
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  uint32_t raddr = 0 ;
  if(vraddr >= 0x80000000) raddr = vraddr - 0x80000000;

  // 总是读取地址为`raddr & ~0x3u`的4字节返回
  uint32_t offset = raddr & 0x3;
  uint32_t res = 0;
  //实现外设的访问
//-----------------------------------------------------------------------------------------//
  if(vraddr >= MMIO_BASE && vraddr < MMIO_END){
    uint32_t res = device_read(vraddr);

#ifdef CONFIG_DTRACE
    if(raddr >=CONFIG_DTRACE_START && raddr < CONFIG_DTRACE_END){
      word_t tmp_array[4];
      for(int i=0;i<4;i++){
        tmp_array[i] = (res & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
      }
      log_write(ANSI_FMT("[DEV]",ANSI_FG_WHITE) 
                ANSI_FMT("[READ ] ",ANSI_FG_RED) 
                ANSI_FMT(FMT_PADDR": ",ANSI_FG_MAGENTA), vraddr);
      for(int i=0;i<4;i++){
        log_write("%02x ", tmp_array[i] );
      }
      log_write(ANSI_FMT("[%s]",ANSI_FG_GREEN), device_get_name((word_t)vraddr));
      log_write("\n");
    }
#endif

    return res;
  }
//-----------------------------------------------------------------------------------------//

  // 实现内存的访问
//-----------------------------------------------------------------------------------------//
  res = ((uint64_t)(cpu.pRAM[(raddr >> 2)+4]) <<  8 * (4 - offset)) | (cpu.pRAM[raddr >> 2] >> (offset * 8)) ;
#ifdef CONFIG_MTRACE
  if(vraddr >=CONFIG_MTRACE_START && vraddr < CONFIG_MTRACE_END){
    word_t tmp_array[4];
    for(int i=0;i<4;i++){
      tmp_array[i] = (res & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
    }
    log_write(ANSI_FMT("[MEM]",ANSI_FG_GREEN) 
              ANSI_FMT("[READ ] ",ANSI_FG_RED) 
              ANSI_FMT(FMT_PADDR": ",ANSI_FG_MAGENTA), vraddr);
    for(int i=0;i<4;i++){
      log_write("%02x ", tmp_array[i] );
    }
    log_write("\n");
  }
#endif
//-----------------------------------------------------------------------------------------//
  return res;
}
void pRAM_write(int vwaddr, int wdata, char wmask) {
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  if(vwaddr >= MMIO_BASE && vwaddr < MMIO_END){
    device_write(vwaddr, wdata);
#ifdef CONFIG_DTRACE
    if(vwaddr >=CONFIG_DTRACE_START && vwaddr < CONFIG_DTRACE_END){
      word_t tmp_array[4];
      for(int i=0;i<4;i++){
        tmp_array[i] = (wdata & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
      }
      log_write(ANSI_FMT("[DEV]",ANSI_FG_WHITE) 
                ANSI_FMT("[WRITE] ",ANSI_FG_BLUE) 
                ANSI_FMT(FMT_PADDR": ",ANSI_FG_CYAN), vwaddr);
      for(int i=0;i<4;i++){
        log_write("%02x ", tmp_array[i] );
      }
      log_write("wmask:%c", wmask);
      log_write(ANSI_FMT("[%s]",ANSI_FG_GREEN), device_get_name((word_t)vwaddr));
      log_write("\n");
    }
#endif
    return ;
  }

  uint32_t waddr = 0 ;
  if(vwaddr >= 0x80000000) waddr = vwaddr - 0x80000000;

  uint32_t offset = waddr & 0x3;
  uint32_t mask_off;
  switch (wmask)
  {
  case 1:
      mask_off = 0x000000ffu << (offset * 8);
      cpu.pRAM[waddr >> 2] = (cpu.pRAM[waddr >> 2] & ~mask_off) | (wdata & 0xffu) << (offset * 8);
    break;
  case 2:
      mask_off = 0x0000ffffu << (offset * 8);
      cpu.pRAM[waddr >> 2] = (cpu.pRAM[waddr >> 2] & ~mask_off) | (wdata & 0xffffu) << (offset * 8);
    break;
  case 4:
      cpu.pRAM[waddr >> 2] = wdata;
    break;
  
  default:
	break;
  }
#ifdef CONFIG_MTRACE
  if(waddr >=CONFIG_MTRACE_START && waddr < CONFIG_MTRACE_END){
    word_t tmp_array[8];
    for(int i=0;i<sizeof(word_t);i++){
      tmp_array[i] = (wdata & (~0xffu >> (8 * i)) ) >> (8 * (3-i));
    }
    log_write(ANSI_FMT("[MEM]",ANSI_FG_GREEN) 
              ANSI_FMT("[WRITE] ",ANSI_FG_BLUE) 
              ANSI_FMT(FMT_PADDR": ",ANSI_FG_CYAN), waddr);
    for(int i=0;i<4;i++){
      log_write("%02x ", tmp_array[i] );
    }
    log_write("wmask:%c\n",wmask);
  }
#endif

}

void pmem_init(char *file)
{
    // 初始化 RAM & ROM
    printf("%s\n",file);
    cpu.pROM = load_riscv32_instructions(file);
    cpu.pRAM = load_riscv32_instructions(file);
    if (!cpu.pROM || !cpu.pRAM) {
		printf("Can not load riscv32_instructions.bin\n");
		assert(0);
    }

}

void pmem_free()
{
	if(cpu.pROM) free(cpu.pROM);
	if(cpu.pRAM) free(cpu.pRAM);
}

//===================================================//