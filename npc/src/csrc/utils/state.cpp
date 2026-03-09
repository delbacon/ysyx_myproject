

#include <utils.h>
extern bool ebreak_flag;

NPCState npc_state = { .state = NPC_STOP };

int is_exit_status_bad() {
  int good = (ebreak_flag == true) || (npc_state.state == NPC_END );
  return !good;
}
