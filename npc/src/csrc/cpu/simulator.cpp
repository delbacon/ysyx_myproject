#include <cpu/isa.h>
#include <cpu/decode.h>

#include <verilated.h>
#include <verilated_fst_c.h>
#include <Vysyx_26020055_top.h>
#include <iostream>

//DPI-C
#include "svdpi.h"
#include "Vysyx_26020055_top__Dpi.h"

static Vysyx_26020055_top* dut = nullptr;
static VerilatedFstC* tfp = nullptr;

static uint64_t sim_time = 0;

// 初始化仿真信号
//============== SIM ===================//
static void sim_once(){
    int n = 2;//推进一个时钟周期
    while(n){
        while (sim_time < 10) {
            dut->clk = !dut->clk;
            dut->eval();
            
            IFDEF(WAVE_TRACE, tfp->dump(sim_time));
            
            sim_time++;
        }
        
        if(sim_time == 10){
            dut->rst = 0;
        }
	    // 時鐘切換
        dut->clk = !dut->clk;

	    //更新
        dut->eval();

        IFDEF(WAVE_TRACE, tfp->dump(sim_time));

	    sim_time++;
        n--;
        //ebreak
    }
}

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

int isa_exec_once(Decode *s) {
    sim_once();
    s->pc   = cpu.pc ;
    s->snpc = cpu.pc + 4; // static next pc
    s->dnpc = cpu.pc ; // dynamic next pc
    s->isa  = cpu.inst;
    return 0;
}

void simulator_end(){
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
//=======================================//


void init_sim(int argc, char** argv){
    simulator_start(argc, argv);
}