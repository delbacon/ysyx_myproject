#include <common.h>

#include <monitor/sdb.h>
#include <memory/paddr.h>

void init_monitor(int argc,char **argv);
int is_exit_status_bad();
void sdb_mainloop() ;
void init_sim(int argc, char** argv);

void engine_start() {

  sdb_mainloop();
}

void sdb_set_batch_mode() ;

int main(int argc, char **argv) {
  // Initialize the monitor. //

  init_monitor(argc, argv);

  //sdb_set_batch_mode() ;
  init_sim(argc,argv);
  // Start engine. //
  engine_start();

  free_pmem();
  return is_exit_status_bad();
}

