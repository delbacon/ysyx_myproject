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

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args,uint8_t n) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args,uint8_t n) {
	nemu_state.state = NEMU_QUIT;
	return -1;
}

static int cmd_help(char *args,uint8_t n);

//单步执行
static int cmd_si_N(char *args,uint8_t n){
  cpu_exec(n);
  return 0;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *,uint8_t);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Execute the program step-by-step for N insts and then pause.If N is not provided, default to 1.", cmd_si_N },

  /* TODO: Add more commands */

};

//cmd中参数的最大数量
#define CMD_ARGS_NUM 2

static struct {
  char * args;
  uint8_t n;
} cmd_args;

int is_int(char *s) {
    if (!s || *s == '\0') return 0;
    
    char *end;
    // 使用 strtol 避免溢出问题
    strtol(s, &end, 10);
    
    // 检查是否完整转换（end 指向结尾）且不是空输入
    return (*end == '\0' && end != s);
}

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args,uint8_t n) {
  n = 0;
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL,0);
    return;
  }
//把rl_gets写在for里面，可以让每次执行完之后重新调用这个函数，去获得新的输入的参数，从而实现
//执行完当前指令后，接着接受下一条指令的操作
  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    char *cmd = strtok(str, " ");

    char *args = NULL;
    for(int j=0;j<CMD_ARGS_NUM;j++){
      /* extract the first token as the command */
      //读取参数到cmd，如果j=0默认不读，因为cmd定义时读取了这个位置的参数
      if(j>0){
//        cmd = strtok(NULL, " ");
          cmd = args;
      }
      if (cmd == NULL) { continue; }

      /* treat the remaining string as the arguments,
       * which may need further parsing
       */
      if (args >= str_end) {
        args = NULL;
      }

      switch(j){
        case 0 :
          cmd_args.args = cmd;
          break;
        
        case 1 :
          cmd_args.n = (uint8_t)is_int(args);
          break;

        default:break;
      }
      args = cmd + strlen(cmd) + 1;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(cmd_args.args,cmd_args.n) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
