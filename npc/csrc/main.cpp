#include "include/simulator.h"
#include "include/monitor.h"



CPU_T cpu = {.pROM=NULL,.pRAM=NULL,.pc=0,.inst=0,.gpr={0},.sim_time=0,.state=0}; 
#define TOPNAME ysyx_26020055_top


// 写log
#define CONFIG_LOG_ENABLE

int main(int argc, char** argv) {
	// 初始化 pROM pRAM
	pmem_init(argc, argv);
	// 初始化 device
    device_init();

    monitor_init();

    // 启动仿真
    simulator_init(argc, argv);
	
	return ebreak_success_print();
  }
