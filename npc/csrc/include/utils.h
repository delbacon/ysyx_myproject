#ifndef __UTILS_H__
#define __UTILS_H__

#include "common.h"

extern "C" void ebreak();

int ebreak_success_print();

// ----------- log -----------

#define ANSI_FG_BLACK   "\33[1;30m"
#define ANSI_FG_RED     "\33[1;31m"
#define ANSI_FG_GREEN   "\33[1;32m"
#define ANSI_FG_YELLOW  "\33[1;33m"
#define ANSI_FG_BLUE    "\33[1;34m"
#define ANSI_FG_MAGENTA "\33[1;35m"
#define ANSI_FG_CYAN    "\33[1;36m"
#define ANSI_FG_WHITE   "\33[1;37m"
#define ANSI_BG_BLACK   "\33[1;40m"
#define ANSI_BG_RED     "\33[1;41m"
#define ANSI_BG_GREEN   "\33[1;42m"
#define ANSI_BG_YELLOW  "\33[1;43m"
#define ANSI_BG_BLUE    "\33[1;44m"
#define ANSI_BG_MAGENTA "\33[1;45m"
#define ANSI_BG_CYAN    "\33[1;46m"
#define ANSI_BG_WHITE   "\33[1;47m"
#define ANSI_NONE       "\33[0m"

#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

#define FMT_PADDR "0x%08x"


#define log_write(...) IFDEF(CONFIG_TRACE, \
  do { \
    extern FILE* log_fp; \
    extern bool log_enable(); \
    if (log_enable() && log_fp != NULL) { \
      fprintf(log_fp, __VA_ARGS__); \
      fflush(log_fp); \
    } \
  } while (0) \
)

#define _Log(...) \
  do { \
    printf(__VA_ARGS__); \
    log_write(__VA_ARGS__); \
  } while (0)

#define Log(format, ...) \
    _Log(ANSI_FMT("[%s:%d %s] " format, ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

        
void log_init(const char *log_file);



// ---------- trace ------------//

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