#include "../../include/simulator.h"

#include "../../include/device.h"
#include "../../include/monitor.h"

#ifdef _NVBOARD
void nvboard_bind_all_pins(TOP_NAME* TOPNAME);
#endif

//每次执行最大可以打印的指令数，超过就不会打印了
#define MAX_INST_TO_PRINT 100


#define SIMULATE_INIT(argc,argv) \


static int g_print_step;
static int g_timer;

// 全局变量,声明仿真对象 dut 和 波形輸出 tfp
// 后面会在 SIMULATE_INIT 中初始化
static Vysyx_26020055_top* dut = nullptr;
static VerilatedFstC* tfp = nullptr;


// 初始化仿真信号
static void simulate_signal_init(){
    dut->clk = 0;
    dut->rst = 1;
}

static void simulator_start(int argc, char** argv){
    // 初始化 Verilator
    Verilated::commandArgs(argc, argv);
    dut = new Vysyx_26020055_top;
#ifdef WAVE_TRACE
    Verilated::traceEverOn(true);
    tfp = new VerilatedFstC;
    
    dut->trace(tfp, 99);
    tfp->open("waveform.fst");
#endif
    // 初始化仿真信号
    simulate_signal_init();
}

static void simulator_end(){
    // simulator_end()
    if(tfp){
        // 關閉波形檔案
        tfp->close();
        printf("close wave file\n");
        // 清理記憶體
        delete tfp;
    }
        delete dut;
}



void exec_once(){
	// 時鐘切換
    dut->clk = !dut->clk;
    if (cpu.sim_time == 10) {
        dut->rst = 0;
    }
	//更新
    dut->eval();

#ifdef WAVE_TRACE
    // 記錄波形
    tfp->dump(cpu.sim_time);
#endif

	cpu.sim_time++;
    //ebreak
	if(cpu.sim_time % 100000000 == 0) reg_display();
}


void execute(uint64_t n){
    if(cpu.state != STATE_RUNNING) return;
    while (n) {
        exec_once();
        n--;
        if(cpu.state == STATE_EBREAK) break;
    }
}

int cpu_exec(uint64_t n){
  g_print_step = (n < MAX_INST_TO_PRINT);
  switch (cpu.state) {
    case STATE_EBREAK:
        printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
        simulator_end();
        return 1;
    default: cpu.state = STATE_RUNNING;
  }

  uint64_t timer_start = get_time_us();
  execute(n);
  uint64_t timer_end = get_time_us();
  g_timer += timer_end - timer_start;

  switch (cpu.state) {
    case STATE_RUNNING: cpu.state = STATE_STOP; break;
  }



    return 0;
}




void simulator_init(int argc, char** argv){
    simulator_start(argc, argv);
    sdb_mainloop();
}
