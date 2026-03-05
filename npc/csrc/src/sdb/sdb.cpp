#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <limits.h>

#include "../../include/simulator.h"


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

  line_read = readline("(npc) ");

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
  cpu.state = STATE_END;
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

  cpu_exec((uint64_t)n);
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
      reg_display();
      break;
    case 'w':
      wp_display();
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

  char *endptr;
  bool success = true;
  long n = strtol(arg_N,&endptr,10);
  word_t addr_s = (word_t)expr(arg_EXPR,&success);
  if(success == false){
    fprintf(stderr, "Warning: use 'x N EXPR' to printf [N] consecutive 4-byte words in hex. .\n");
    return 1;
  }
  // 判断输入是否为数字
  if (*endptr != '\0') {
    fprintf(stderr, "Error: Invalid input '%s'. Expected a number.\n", arg_N);
    return 1;
  }
  
  for(int i=0;i<n;i++){
    word_t addr = addr_s + i*4;
    printf("addr 0x%x: 0x%08x\n",addr,pRAM_read(addr));
  }
  return 0;
}

//表达式计算
static int cmd_p_EXPR(char *args){
  bool success;
  word_t res = expr(args,&success);
  if(!success){
    printf("Invalid expression.\n");
    return 1;
  }


  printf("EXPR expressed:0d:%u  0x%x\n",res,res);
  return 0;
}

//监视点设置
static int cmd_w_EXPR(char *args){ 
  bool success;
  if(args==NULL){
    printf("Warning: use 'w EXPR' to set watchpoint. .\n");
    return 1;
  }
  word_t res = expr(args,&success);
  if(!success){
    printf("Invalid expression.\n");
    return 1;
  }
  wp_watch(args,res);
  printf("Set watchpoint at addr:0x%x\n",res);
  return 0;
}

//监视点删除
static int cmd_d_N(char *args){ 
  char *arg_N = strtok(NULL," ");
  char *endptr;
  long n = strtol(arg_N,&endptr,10);
  if(n<0){
    printf("Warning: Negative value '%ld' ignored. Deletion skipped.\n", n);
    return 1;
  }
  if(n>=NR_WP){
    printf("Warning: Watchpoint [%ld] does not exist. Deletion skipped.\n", n);
    return 1;
  }
  remove_wp(n);
  printf("Delete watchpoint [%ld]\n", n);
  return 0;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NPC", cmd_q },
  /* TODO: Add more commands */
  { "si", "Execute the program step-by-step for N instructions and then pause.If N is not provided, default to 1.", cmd_si_N },
  { "info", "use 'r' to printf reg; use 'w' to printf watchpoint.", cmd_info },
  { "x", "Compute [EXPR] as a starting address and output [N] consecutive 4-byte words in hex.", cmd_x_N_EXPR },
  { "p", "Evaluate an expression EXPR and print the result.", cmd_p_EXPR },
  { "w", "Set watchpoint addr:[EXPR]", cmd_w_EXPR },
  { "d", "Delete watchpoint [N]", cmd_d_N },
  
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
