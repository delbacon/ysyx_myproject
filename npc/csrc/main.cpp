//include
#include "include/memory.h"
#include "include/device.h"
#include "include/utils.h"
#include "include/cpu.h"
#include "include/simulator.h"
#include "include/monitor.h"


CPU_T cpu = {0}; 
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
