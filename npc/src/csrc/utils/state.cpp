

#include <utils.h>
#include <cpu/isa.h>
extern bool ebreak_flag;

NPCState npc_state = { .state = NPC_STOP };

int is_exit_status_bad() {
  int good = (ebreak_flag == 1 && cpu.gpr[10] == 0);
  return !good;
}
