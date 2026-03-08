#include "simulator.h"
#include "sdb.h"
#include "device.h"
#include "monitor.h"
#include "utils.h"
#include "difftest.h"

#ifdef _NVBOARD
void nvboard_bind_all_pins(TOP_NAME* TOPNAME);
#endif



#define SIMULATE_INIT(argc,argv) \

void init_disasm();
void difftest_step(vaddr_t pc, vaddr_t npc) ;
void difftest_skip_ref() ;

uint64_t g_nr_guest_inst = 0;
static int g_print_step = false;
static int g_timer;
static ring_buffer_t itrace_cb;

// 声明仿真对象 dut 和 波形輸出 tfp
// 后面会在 SIMULATE_INIT 中初始化
static Vysyx_26020055_top* dut = nullptr;
static VerilatedFstC* tfp = nullptr;




// 初始化仿真信号
//============== SIM ===================//
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
    //写在这里，只有结束仿真的时候才会写到log里
#ifdef CONFIG_ITRACE_LASTEST
        if (cpu.state != STATE_RUNNING) {
            itrace_log_write(&itrace_cb);
        }
#endif
}
//=======================================//
static void trace_and_difftest(CPU_T s){
    int ilen = sizeof(word_t);
    word_t inst = s.inst;
    word_t pc = s.pc;
#ifdef CONFIG_ITRACE
    char c[256];
    char *start = c;

    uint8_t *inst_str = (uint8_t *)malloc(ilen);
    
    start += snprintf(start, 64, ANSI_FMT("0x%08x: ",ANSI_FG_BLUE) ANSI_FG_CYAN, pc);
    for (int i = sizeof(cpu.inst) - 1; i >= 0; i --) {
        uint8_t byte = (inst >> (8 * i)) & 0xff;
        start += snprintf(start, 4, " %02x", byte);
        inst_str[i] = byte;
    }
    start += snprintf(start, 16, ANSI_NONE "\t\t");
    void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
    //跳过初始化时产生的 0x00000000 指令,避免反汇编失败
    
    if (inst != 0x0){
        disassemble(start, 64, (uint64_t)pc, inst_str, ilen);
    }
    // 打印指令(<N)
    inst_print_N(g_print_step, c);
    free(inst_str);
#endif



#ifdef CONFIG_ITRACE_LASTEST
    itrace_buf_write(&itrace_cb, c);
#elif CONFIG_ITRACE
    log_write("%s\n", c); 
#endif

#ifdef CONFIG_FTRACE
    word_t rd = get_rd(inst);
    word_t dnpc = s.dnpc;

    // 判断是否为 jal 或 jalr 指令
    if (is_jal(inst)) {
        // jal 指令：跳转并链接
        //printf("[FTRACE] JAL instruction detected at inst 0x%08x\n", inst);
        // 在这里添加你的 FTRACE 逻辑
        if(rd == 1) ftrace_call(pc, dnpc); 

    } else if (is_jalr(inst)) {
        uint32_t imm = get_jalr_imm(inst);
        // jalr 指令：寄存器跳转并链接
        //printf("[FTRACE] JALR instruction detected at inst 0x%08x\n", inst);
        // 在这里添加你的 FTRACE 逻辑
        if(s.inst == 0x00008067) ftrace_ret(pc);
        else if (rd == 1) ftrace_call(pc, dnpc);
        else if (rd == 0 && imm == 0) ftrace_call(pc, dnpc); 
        // jr rs1 -> jalr x0, 0(rs1), which may be other control flow e.g. 'goto','for'
    }
#endif

#ifdef CONFIG_DIFFTEST
    difftest_step(pc, s.dnpc);
#endif
    IFDEF(CONFIG_WATCHPOINT,wp_difftest());

}
void exec_once(){
    int n = 2;//推进一个时钟周期
    while(n){
        while (cpu.sim_time < 10) {
            dut->clk = !dut->clk;
            dut->eval();    
            cpu.sim_time++;
        }
        
        if(cpu.sim_time == 10){
            dut->rst = 0;
        }
	    // 時鐘切換
        dut->clk = !dut->clk;

	    //更新
        dut->eval();

#ifdef WAVE_TRACE
        // 記錄波形
        tfp->dump(cpu.sim_time);
#endif

	    cpu.sim_time++;
        n--;
        //ebreak
    }
    g_nr_guest_inst++;
}


void execute(uint64_t n){

    while (n) {
        exec_once();

        trace_and_difftest(cpu);

        //如果nemu的状态为NEMU_RUNNING，则继续执行，否则跳出循环
        if (cpu.state != STATE_RUNNING) {

            break;
        }

        n--;
    }
}

int cpu_exec(uint64_t n){
//每次执行最大可以打印的指令数，超过就不会打印了
#ifdef CONFIG_MAX_INST_TO_PRINT
  g_print_step = (n < CONFIG_MAX_INST_TO_PRINT);
#else
  g_print_step = (n < 100);
#endif 
  switch (cpu.state) {
    case STATE_EBREAK:case STATE_END:
        printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
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
    init_disasm();
    itrace_init(&itrace_cb);

    simulator_start(argc, argv);
    sdb_mainloop();
    simulator_end();
}
