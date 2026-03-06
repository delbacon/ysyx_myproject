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
  uint32_t addr = raddr >> 2;
  uint32_t res = 0;
  //实现外设的访问

  if(vraddr >= MMIO_BASE && vraddr < MMIO_END){
    return device_read(vraddr);
  }

  res = cpu.pRAM[addr] >> (offset * 8);    
  switch(offset){
    case 1: return ((cpu.pRAM[addr+4] & 0x000000ff) << 24) + res;
    case 2: return ((cpu.pRAM[addr+4] & 0x0000ffff) << 16) + res;
    case 3: return ((cpu.pRAM[addr+4] & 0x00ffffff) <<  8) + res;
    default: return res;
  }
}
void pRAM_write(int vwaddr, int wdata, char wmask) {
  
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  if(vwaddr >= MMIO_BASE && vwaddr < MMIO_END){
    device_write(vwaddr, wdata);
    return ;
  }

  uint32_t waddr = 0 ;
  if(vwaddr >= 0x80000000) waddr = vwaddr - 0x80000000;

  uint32_t offset = waddr & 0x3;
  uint32_t addr = waddr >> 2;
  uint32_t mask_off;
  switch (wmask)
  {
  case 1:
      mask_off = 0x000000ffu << (offset * 8);
      cpu.pRAM[addr] = (cpu.pRAM[addr] & ~mask_off) | (wdata & 0xffu) << (offset * 8);
    break;
  case 2:
      mask_off = 0x0000ffffu << (offset * 8);
      cpu.pRAM[addr] = (cpu.pRAM[addr] & ~mask_off) | (wdata & 0xffffu) << (offset * 8);
    break;
  case 4:
      cpu.pRAM[addr] = wdata;
    break;
  
  default:
	break;
  }
}

void pmem_init(int argc, char** argv)
{
    // 初始化 RAM & ROM
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <riscv32_instructions.bin>\n", argv[0]);
        assert(0);
    }
    cpu.pROM = load_riscv32_instructions(argv[1]);
    cpu.pRAM = load_riscv32_instructions(argv[1]);
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