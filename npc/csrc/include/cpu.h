#ifndef __CPU_H__
#define __CPU_H__ 

// include/cpu.h

#include "common.h"
#include "utils.h"
#include <stdint.h>

// 定义可能的运行状态
enum{
    STATE_START,STATE_EBREAK,STATE_ABORT,STATE_RUNNING,STATE_STOP,STATE_END,
};


// 定义结构体
typedef struct {
    uint32_t *pROM;
    uint32_t *pRAM;
    uint32_t pc;
    uint32_t gpr[32];
    int sim_time;
    int state;
} CPU_T;

// 声明全局变量（extern 表示“在别处定义”）
extern CPU_T cpu;


extern "C" void pc_get(int val);

extern "C" void reg_get(int reg_idx, int val);

void reg_display() ;

word_t reg_str2val(const char *s, bool *success);


#endif // __CPU_H__
