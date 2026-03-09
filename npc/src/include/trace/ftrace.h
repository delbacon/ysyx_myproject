#ifndef __FTRACE_H__
#define __FTRACE_H__ 

#include <common.h>

//----- ftrace -----//
//存储 elf 文件中函数名和对应地址范围的结构体
typedef struct {
    char *name;
    word_t start;  
    word_t end;    
    word_t size;   
} ElfFunction;

//函数声明

void ftrace_call(vaddr_t pc, vaddr_t pc_target);
void ftrace_ret(vaddr_t pc);
int  init_ftrace(const char *elf_file);
void ftrace_free(ElfFunction *funcs);
#endif