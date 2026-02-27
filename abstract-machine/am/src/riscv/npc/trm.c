#include <am.h>
#include <klib-macros.h>
#include <stdio.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
static const char mainargs[MAINARGS_MAX_LEN] = TOSTRING(MAINARGS_PLACEHOLDER); // defined in CFLAGS

    //如果执行到ebreak,则打印测试通过
//asm volatile 作用是插入一条汇编代码（asm），并且不让编译器优化（volatile）
#define ebreak(code) \
  asm volatile("mv a0, %0; ebreak" : :"r"(code));

void putch(char ch) {
}

void halt(int code) {

  ebreak(code);
  while (1);
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
