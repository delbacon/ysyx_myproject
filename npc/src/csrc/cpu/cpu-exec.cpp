/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>
#include <monitor/sdb.h>
#include <utils.h>
#include <trace/itrace.h>

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 100

CPU_state cpu = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0; // unit: us
static bool g_print_step = false;
uint64_t get_time_us();
void device_update();



static void trace_and_difftest(Decode *_this, vaddr_t dnpc){
  MUXDEF(CONFIG_ITRACE_LASTEST,itrace_list_put(_this->logbuf);
                              ,log_write("%s\n", _this->logbuf);)
  
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }
  
  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));

  //打开wp_difftest
  IFDEF(CONFIG_WATCHPOINT, wp_difftest());

}

static void exec_once(Decode *s, vaddr_t pc) {
  //snpc指向地址上的下一条指令，dnpc指向实际要执行的下一条指令
  //静态指令是指程序代码中的指令, 动态指令是指程序运行过程中的指令
  //实际执行的是dnpc,所以在执行指令的过程中应该正确维护dnpc
  //isa这里取出指令到s->isa.inst中，并默认pc+len（len根据传参确定）,然后令dnpc等于snpc
  cpu.pc = pc;
  isa_exec_once(s);
  cpu.pc = s->dnpc;

  IFDEF(CONFIG_ITRACE, itrace_list_write(s));
}
//执行一条指令
static void execute(uint64_t n) {
  Decode s;

  IFDEF(CONFIG_ITRACE_LASTEST, itrace_list_init());

  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);
    g_nr_guest_inst ++;
    
    trace_and_difftest(&s, cpu.pc);
    
    //如果nemu的状态为NPC_RUNNING，则继续执行，否则跳出循环
    if(npc_state.state != NPC_RUNNING) {
      IFDEF(CONFIG_ITRACE_LASTEST, itrace_log_write());

      break;
    }
  }
}

static void statistic() {
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) {
    Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  }else {
    Log("Finish running in less than 1 us and can not calculate the simulation frequency");
  }
}

void assert_fail_msg() {
  isa_reg_display();
  statistic();
}

/* Simulate how the CPU works. */
int cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);

  switch (npc_state.state) {
    case NPC_END: case NPC_ABORT: case NPC_QUIT:
      Log("cpu-exec:pc:%x\n",cpu.pc);
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return 1;
    default: npc_state.state = NPC_RUNNING;
  }

  uint64_t timer_start = get_time_us();

  execute(n);

  uint64_t timer_end = get_time_us();
  g_timer += timer_end - timer_start;

  switch (npc_state.state) {
    case NPC_RUNNING: npc_state.state = NPC_STOP; break;

    case NPC_END: case NPC_ABORT:
      simulator_end();
      Log("nemu: %s at pc = " FMT_WORD,
          (npc_state.state == NPC_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
           (npc_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          cpu.pc);
      // fall through
    case NPC_QUIT: statistic();
  }
  return 0;
}
