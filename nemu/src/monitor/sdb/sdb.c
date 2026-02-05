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
#include "memory/paddr.h"
#include <limits.h>


#define TOKEN_SIZE 64

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

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);

//单步执行
//-----------------------------//
static int cmd_si_N(char *args) {
  char *arg = strtok(NULL," ");

  if(arg == NULL) {
    cpu_exec(1);
    return 0;
  }

  char *endptr;
  long n = strtol(arg,&endptr,10);
  
  // 判断输入是否为数字
  if (*endptr != '\0'){
    fprintf(stderr, "Error: Invalid input '%s'. Expected a number.\n", arg);
    return 1;
  }

  // 处理负数输入
  if (n < 0) {
    fprintf(stderr, "Warning: Negative value '%ld' ignored. Execution skipped.\n", n);
    return 1;
  }

  cpu_exec((uint32_t)n);
  return 0;
}
//-----------------------------//



//查看reg或者watchpoint的信息
static int cmd_info(char *args){
  char *arg = strtok(NULL," ");

  if(arg==NULL){
    fprintf(stderr, "Warning: use 'r' to printf reg; use 'w' to printf watchpoint. .\n");
    return 1;
  } 

  switch(*arg){
    case 'r':
      isa_reg_display();
      break;

    default: break;
  }
  return 0;
}



//输出内存
static int cmd_x_N_EXPR(char *args){
  char *arg_N = strtok(NULL," ");
  char *arg_EXPR = strtok(NULL," ");
  // 判断输入是否为空
  if(arg_N == NULL || arg_EXPR == NULL) {
    fprintf(stderr, "Warning: use 'x N EXPR' to printf [N] consecutive 4-byte words in hex. .\n");
    return 1;
  }

  char *endptr,*endptr2;
  long n = strtol(arg_N,&endptr,10);
  paddr_t addr_s = (paddr_t)(strtol(arg_EXPR,&endptr2,0));
  // 判断输入是否为数字
  if (*endptr != '\0' || *endptr2 !='\0' ) {
    fprintf(stderr, "Error: Invalid input '%s'. Expected a number.\n", arg_N);
    return 1;
  }
  
  for(int i=0;i<n;i++){
    paddr_t addr = addr_s + i*4;
    printf("%x: %08x\n",addr,paddr_read(addr,4));
  }
  return 0;
}

static int cmd_p_EXPR(char *args){
  bool success;
  word_t res = expr(args,&success);
  if(!success){
    printf("Invalid expression.\n");
    return 1;
  }
  printf("%d\n",res);
  return 0;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  /* TODO: Add more commands */
  { "si", "Execute the program step-by-step for N instructions and then pause.If N is not provided, default to 1.", cmd_si_N },
  { "info", "use 'r' to printf reg; use 'w' to printf watchpoint.", cmd_info },
  { "x", "Compute [EXPR] as a starting address and output [N] consecutive 4-byte words in hex.", cmd_x_N_EXPR },
  { "p", "Evaluate an expression EXPR and print the result.", cmd_p_EXPR },
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
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
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
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
