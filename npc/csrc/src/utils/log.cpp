#include "../../include/common.h"
#include "../../include/utils.h"

extern int g_nr_guest_inst;
FILE *log_fp = NULL;

void log_init(const char *log_file) {
  log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    if(fp==NULL){
      printf("Can not open '%s'", log_file);
      assert(0);
    }
    log_fp = fp;
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");
}

bool log_enable() {
  return MUXDEF(CONFIG_TRACE, (g_nr_guest_inst >= CONFIG_TRACE_START) &&
         (g_nr_guest_inst <= CONFIG_TRACE_END), false);
}
