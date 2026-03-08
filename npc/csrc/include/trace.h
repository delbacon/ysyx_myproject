#ifndef __TRACE_H__
#define __TRACE_H__ 

#include "common.h"

//----- itrace -----//  
// 换行缓冲区大小
#ifdef CONFIG_ITRACE_LASTEST_N
#define RING_BUFFER_SIZE CONFIG_ITRACE_LASTEST_N
#else
#define RING_BUFFER_SIZE 32
#endif


typedef struct {
  char buf[RING_BUFFER_SIZE][128];
  size_t head;
  size_t tail;
  int cnt;
} ring_buffer_t;

void inst_print_N(int g_print_step, char *c);

void itrace_init(ring_buffer_t *cb);
void itrace_buf_write(ring_buffer_t *cb, char *c);

void itrace_log_write(ring_buffer_t *cb);


//----- ftrace -----//
//存储 elf 文件中函数名和对应地址范围的结构体
typedef struct {
    char *name;
    word_t start;  
    word_t end;    
    word_t size;   
} ElfFunction;

//函数声明
int parse_elf_functions_with_size(ElfFunction **out_funcs, char *elf_data);
void free_elf_functions(ElfFunction *funcs, int count);

void ftrace_call(word_t pc, word_t pc_target);
void ftrace_ret(word_t pc);

#endif