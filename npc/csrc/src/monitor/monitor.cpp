#include "../../include/monitor.h"
#include <getopt.h>
#include "../../include/debug.h"
#include "../../include/cpu.h"
#include "../../include/utils.h"


static char *log_file = NULL ;
static char *img_file = NULL;
static char *elf_file = NULL;

void init_log(const char *log_file);
void init_sdb();
int  init_elf_file(const char *elf_file);
void pmem_init(char *file);

static void welcome() {
  Log("Trace: %s", MUXDEF(CONFIG_LOG_ENABLE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
  IFDEF(CONFIG_LOG_ENABLE, Log("If trace is enabled, a log file will be generated "
        "to record the trace. This may lead to a large log file. "
        "If it is not necessary, you can disable it in menuconfig"));
  Log("Build time: %s, %s", __TIME__, __DATE__);
  printf("Welcome to " ANSI_FMT("riscv32", ANSI_FG_YELLOW ANSI_BG_RED) "-NPC!\n" );
  printf("For help, type \"help\"\n");
}

void sdb_set_batch_mode();

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"batch"    , no_argument      , NULL, 'b'},
    {"log"      , required_argument, NULL, 'l'},
    //{"diff"     , required_argument, NULL, 'd'},
    //{"port"     , required_argument, NULL, 'p'},
    {"elf-input", required_argument, NULL, 'e' },
    {"help"     , no_argument      , NULL, 'h'},
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-bhl:d:p:", table, NULL)) != -1) {
    switch (o) {
      case 'b': sdb_set_batch_mode(); break;
      //case 'p': sscanf(optarg, "%d", &difftest_port); break;
      case 'l': log_file = optarg; break;
      //case 'd': diff_so_file = optarg; break;
      case 'e': elf_file = optarg; break;
      case 1: img_file = optarg;break;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\t-b,--batch              run with batch mode\n");
        printf("\t-l,--log=FILE           output log to FILE\n");
        printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
        printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
        printf("\t-e,--elf-input=FILE      input elf file");  
        printf("\n"); 
        exit(0);
    }
  }
  return 0;
}



void monitor_init(int argc,char **argv) {
  /* Parse args */
  parse_args(argc, argv);

  /* Open the log file. */
  log_init(log_file);

  /* Initialize the simple debugger. */
  init_sdb();

  /* Initialize elf file. */
  init_elf_file(elf_file);

  /* Initialize the physical memory. */
  pmem_init(img_file);

  /* Display welcome message. */
  welcome();
}