#ifndef __ITRACE_H__
#define __ITRACE_H__ 

#include <common.h>


//----- itrace -----//  
#define RING_BUFFER_SIZE  MUXDEF(CONFIG_ITRACE_LASTEST_N, CONFIG_ITRACE_LASTEST_N, 32)

typedef struct {
  char buf[RING_BUFFER_SIZE][128];
  size_t head;
  size_t tail;
  int cnt;
} ring_buffer_t;

void itrace_log_write();

void itrace_list_write(Decode *s);

int itrace_list_put(char *c);

void itrace_list_init();


#endif