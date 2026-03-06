#include "../../include/monitor.h"
#include <getopt.h>
#include "../../include/debug.h"
#include "../../include/cpu.h"
#include "../../include/utils.h"


static const char *log_file = "build/npc-log.txt" ;

void init_log(const char *log_file);
void init_sdb();

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

void monitor_init() {

  /* Open the log file. */
  init_log(log_file);

  /* Initialize the simple debugger. */
  init_sdb();

  /* Display welcome message. */
  welcome();
}