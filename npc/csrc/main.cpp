#include "include/simulator.h"
#include "include/monitor.h"


CPU_T cpu = {.pROM=NULL,.pRAM=NULL,.pc=0,.dnpc=0,.inst=0,.gpr={0},.sim_time=0,.state=0}; 
#define TOPNAME ysyx_26020055_top

int main(int argc, char** argv) {
	// 初始化 device
    device_init();

    // 初始化 monitor
    monitor_init(argc, argv);

    // 启动仿真
    simulator_init(argc, argv);
	
	return ebreak_success_print();
  }
