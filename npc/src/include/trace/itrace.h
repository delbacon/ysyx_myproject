#ifndef __TRACE_ITRACE_H__
#define __TRACE_ITRACE_H__ 

#include <common.h>
#include <macro.h>

//----- itrace -----//  
//#define RING_BUFFER_SIZE  MUXDEF(CONFIG_ITRACE_LASTEST, CONFIG_ITRACE_LASTEST_N, 32)
#define RING_BUFFER_SIZE  MUXDEF(CONFIG_ITRACE_LASTEST, CONFIG_ITRACE_LASTEST_N, 32)
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