//#include <nvboard.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <Vysyx_26020055_top.h>
#include <iostream>

//DPI-C
#include "svdpi.h"
#include "Vysyx_26020055_top__Dpi.h"

//
#include "mem_load.h"


#define MAX_TIME 20000
#define TOPNAME ysyx_26020055_top

#define CONCAT_V(x) V##x

//void nvboard_bind_all_pins(TOP_NAME* TOPNAME);

uint32_t PROM[64] = //{0x00a00093,0x00508113,0xffd10193};
//  {0x01400513,0x010000e7,0x00c000e7,0x00100073,0x00a50513,0x00008067};
//  {0x123452b7,0x80000337,0xFFFFF3B7,0x123452b7,0x00100073};
//{0x12345337,0x67830313,0x0ab00393,0x0062a023,0x00728223,0x0002a503,0x0042c583,0x00100073};
{
0x00000513,
0x123455b7,
0x67858593,
0x00b52023,
0x05500613,
0x00c500a3,
0x0a300693,
0x00d501a3,
0x00054703,
0x00150783,
0x00254283,
0x00354283,
0x00100073};

uint32_t *pROM = NULL;
uint32_t *pRAM = NULL;

//#define PROM_READ

//pcROM
//===================================================//
extern "C" int pROM_read(int raddr) {
#ifdef PROM_READ
  return PROM[(raddr>>2)];
#else
  return pROM[(raddr>>2)];
#endif
}
//===================================================//


static int ebreak_flag = 0;
void ebreak()
{
  ebreak_flag = 1;
}

//RAM
//===================================================//
extern "C" int pmem_read(int raddr) {
  // 总是读取地址为`raddr & ~0x3u`的4字节返回
  uint32_t offset = raddr & 0x3;
  uint32_t addr = raddr >> 2;
  uint32_t res = pRAM[addr] >> (offset * 8);
  switch(offset){
    case 1: return ((pRAM[addr+4] & 0x000000ff) << 24) + res;
    case 2: return ((pRAM[addr+4] & 0x0000ffff) << 16) + res;
    case 3: return ((pRAM[addr+4] & 0x00ffffff) <<  8) + res;
    default: return res;
  }
}
extern "C" void pmem_write(int waddr, int wdata, char wmask) {
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
  uint32_t offset = waddr & 0x3;
  uint32_t addr = waddr >> 2;
  uint32_t mask_off;
  switch (wmask)
  {
  case 1:
      mask_off = 0x000000ffu << (offset * 8);
      pRAM[addr] = (pRAM[addr] & ~mask_off) | (wdata & 0xffu) << (offset * 8);
    break;
  case 2:
      mask_off = 0x0000ffffu << (offset * 8);
      pRAM[addr] = (pRAM[addr] & ~mask_off) | (wdata & 0xffffu) << (offset * 8);
    break;
  case 4:
      pRAM[addr] = wdata;
    break;
  
  default:
    break;
  }
}
//===================================================//

int main(int argc, char** argv) {
    // 初始化 RAM & ROM
    pROM = read_to_MEM("./resources/sum.hex");
    pRAM = read_to_MEM("./resources/sum.hex");
    // 初始化 Verilator
    Verilated::commandArgs(argc, argv);
    // 創建 DUT (Design Under Test)
    Vysyx_26020055_top* dut = new Vysyx_26020055_top;

    // 設置波形追蹤
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("waveform.vcd");

    // 初始化信號
    dut->clk = 0;
    dut->rst = 1;
  
    // 模擬時間
    int sim_time = 0;

    // 運行模擬
  	while (sim_time < MAX_TIME) {

	   	// 時鐘切換
        dut->clk = !dut->clk;
        
        // 在時間 10 釋放 reset
        if (sim_time == 10) {
            dut->rst = 0;
        }
		    dut->eval();

        // 評估模型
        printf("pc:%x   simtime:%x  ",(dut->pc),sim_time);
        printf("jmpop:%x  inst:%8x\n",dut->jmp_op,dut->inst);
        // 記錄波形
        tfp->dump(sim_time);
/*        
        // 顯示輸出（僅在時鐘正緣且非 reset 時）
        if (dut->clk && !dut->rst) {
            std::cout << "Time: " << sim_time 
                      << " Count: " << (int)dut->count << std::endl;
        }
  */    
        //ebreak
        if(ebreak_flag) break;

        sim_time++;
    }
    
    // 關閉波形檔案
    tfp->close();
    
    // 清理記憶體
    delete tfp;
    delete dut;
    for(int i=0;i<5;i++){
      printf("RAM[%d]:%x\n",i,pRAM[i]);
    }
    std::cout << "Simulation completed!" << std::endl;

    return 0;
  }
