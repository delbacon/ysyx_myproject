//#include <nvboard.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <Vysyx_26020055_top.h>
#include <iostream>

//DPI-C
#include "svdpi.h"
#include "Vysyx_26020055_top__Dpi.h"

//get time
#include <sys/time.h>  

//
#include "mem_load.h"
#include "readbin.h"


#define MAX_TIME 5000000000
#define TOPNAME ysyx_26020055_top

#define CONCAT_V(x) V##x

#define CONFIG_RTC_MMIO 0x10000000 + 0x0000048

//void nvboard_bind_all_pins(TOP_NAME* TOPNAME);

//uint32_t PROM[64] = //{0x00a00093,0x00508113,0xffd10193};
//  {0x01400513,0x010000e7,0x00c000e7,0x00100073,0x00a50513,0x00008067};
//  {0x123452b7,0x80000337,0xFFFFF3B7,0x123452b7,0x00100073};
//{0x12345337,0x67830313,0x0ab00393,0x0062a023,0x00728223,0x0002a503,0x0042c583,0x00100073};
//{0x00000513,0x123455b7,0x67858593,0x00b52023,0x05500613,0x00c500a3,0x0a300693,0x00d501a3,0x00054703,0x00150783,0x00254283,0x00354283,0x00100073};

uint32_t *pROM = NULL;
uint32_t *pRAM = NULL;

//#define PROM_READ
//#define _DEBUG

uint64_t get_time_us() {
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
        return 0; // 失败
    }
    return (uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)(ts.tv_nsec / 1000);
}
uint64_t time_start = get_time_us();
//pcROM
//===================================================//
extern "C" int pROM_read(int vraddr) {
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  uint32_t raddr = 0;
  if(vraddr >= 0x80000000) raddr = vraddr - 0x80000000;

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
extern "C" int pmem_read(int vraddr) {
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  uint32_t raddr = 0 ;
  if(vraddr >= 0x80000000) raddr = vraddr - 0x80000000;

  // 总是读取地址为`raddr & ~0x3u`的4字节返回
  uint32_t offset = raddr & 0x3;
  uint32_t addr = raddr >> 2;
  uint32_t res = 0;
  //实现外设的访问
  time_t now;
  time(&now);
  struct tm *local_tm = localtime(&now);

  // 3. 提取各部分到 int 变量
  uint32_t year  = local_tm->tm_year + 1900;  // tm_year 是从 1900 年开始的偏移
  uint32_t month = local_tm->tm_mon + 1;      // tm_mon 范围是 0~11，所以 +1
  uint32_t day   = local_tm->tm_mday;         // 1~31
  uint32_t hour  = local_tm->tm_hour;         // 0~23
  uint32_t min   = local_tm->tm_min;          // 0~59
  uint32_t sec   = local_tm->tm_sec;          // 0~61（考虑闰秒）
  if (vraddr == CONFIG_RTC_MMIO){
    res = (uint32_t)(get_time_us() - time_start);return res;
  }else if(vraddr == (CONFIG_RTC_MMIO + 4)){
    res = (uint32_t)((get_time_us() - time_start) >> 32);return res;
  }else if(vraddr == CONFIG_RTC_MMIO + 8){
    res = sec;return res;
  }else if(vraddr == CONFIG_RTC_MMIO + 12){
    res = min;return res;
  }else if(vraddr == CONFIG_RTC_MMIO + 16){
    res = hour;return res;
  }else if(vraddr == CONFIG_RTC_MMIO + 20){
    res = day;return res;
  }else if(vraddr == CONFIG_RTC_MMIO + 24){
    res = month;return res;
  }else if(vraddr == CONFIG_RTC_MMIO + 28){
    res = year;return res;
  }else{
    res = pRAM[addr] >> (offset * 8);
  }  
  switch(offset){
    case 1: return ((pRAM[addr+4] & 0x000000ff) << 24) + res;
    case 2: return ((pRAM[addr+4] & 0x0000ffff) << 16) + res;
    case 3: return ((pRAM[addr+4] & 0x00ffffff) <<  8) + res;
    default: return res;
  }
}
extern "C" void pmem_write(int vwaddr, int wdata, char wmask) {
  
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  if(vwaddr == 0x10000000) { 
    putchar((uint8_t)(wdata & 0xffu));
    return ;
  }
  //printf("%x  %c\n",vwaddr,(char)wdata);
  uint32_t waddr = 0 ;
  if(vwaddr >= 0x80000000) waddr = vwaddr - 0x80000000;

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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <riscv32_instructions.bin>\n", argv[0]);
        return EXIT_FAILURE;
    }
    pROM = load_riscv32_instructions(argv[1]);
    pRAM = load_riscv32_instructions(argv[1]);
    if (!pROM || !pRAM) {
        return EXIT_FAILURE;
    }
#ifdef _DEBUG
    for (size_t i = 0; i < 10; i++) {  // 打印前10条
        printf("instr[%zu] = 0x%08X\n", i, pROM[i]);
    }
    printf("\n");
    for (size_t i = 0; i < 10; i++) {  // 打印前10条
        printf("instr[%zu] = 0x%08X\n", i, pRAM[i]);
    }
#endif

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
    //sim_time < MAX_TIME
    // 運行模擬
  	while (1) {

	   	// 時鐘切換
        dut->clk = !dut->clk;
        
        // 在時間 10 釋放 reset
        if (sim_time == 10) {
            dut->rst = 0;
        }

        dut->eval();
        // 評估模型
        if(dut->pc == 0x7f4) {
          printf("Stop  pc:%x\n",dut->pc);
          break;
        }
#ifdef _DEBUG
        if(dut->clk){
          printf("pc:%x   simtime:%x  ",(dut->pc),sim_time);
          printf("jmpop:%x  inst:%8x\n",dut->jmp_op,dut->inst);
        }
#endif

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
    //如果执行到ebreak,则打印测试通过

    printf("Simulation ended at time %d   pc:%x\n", sim_time,dut->pc);

    // 關閉波形檔案
    tfp->close();
    
    // 清理記憶體
    delete tfp;
    delete dut;

    #ifdef _DEBUG
    for(int i=0;i<5;i++){
      printf("RAM[%d]:%x\n",i,pRAM[i]);
    }
#endif

    if (pROM) free(pROM);
    if (pRAM) free(pRAM);

    std::cout << "Simulation completed!" << std::endl;
    if(ebreak_flag){
      printf("\033[1;30;32mHIT GOOD TRAP\033[0m\n");
      return 0;
    }else {
      printf("\033[1;30;31mHIT BAD TRAP\033[0m\n");
      return -1;
    }
    return 0;
  }
