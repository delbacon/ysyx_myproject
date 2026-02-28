#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

//创建了一个全局变量 addr 用于存储已经分配的地址的指针
//如果 addr 未初始化（为 NULL ），初始化为 heap.start （栈顶）
//每次调用 malloc() 时，会从 addr 开始分配 size 个字节的内存，并返回该内存的起始地址。
static void *addr = NULL;
void *malloc(size_t size) {
  if(addr == NULL){
    addr = heap.start;
  }

  void *tmp = addr;
  if (addr+size < heap.end) {
    addr += size;
    return tmp;
  }else {
    return NULL;
  }

  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  panic("Not implemented");
#endif
  return NULL;
}

void free(void *ptr) {
}

#endif
