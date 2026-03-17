#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <riscv/riscv.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

#define SERIAL_PORT 0x10000000

Area heap = RANGE(&_heap_start, PMEM_END);
static const char mainargs[MAINARGS_MAX_LEN] = TOSTRING(MAINARGS_PLACEHOLDER); // defined in CFLAGS

//如果执行到ebreak,则打印测试通过
//asm volatile 作用是插入一条汇编代码（asm），并且不让编译器优化（volatile）
#define ebreak(code) \
  asm volatile("mv a0, %0; ebreak" : :"r"(code));

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  ebreak(code);
  while (1);
}


static char *print_u32_as_bytes(uint32_t value) {
    // 使用静态缓冲区以避免返回局部变量地址
    static char buffer[4];
    buffer[0] = (char)((value >> 24) & 0xFF); // MSB
    buffer[1] = (char)((value >> 16) & 0xFF);
    buffer[2] = (char)((value >> 8)  & 0xFF);
    buffer[3] = (char)( value        & 0xFF); // LSB
    return buffer;
}
void _trm_init() {
  
  uint32_t ysyx,my_id;
  asm volatile("csrr %0, mvendorid": "=r"(ysyx));
  asm volatile("csrr %0, marchid": "=r"(my_id));
  printf("ysyx_id: %s_%d\n",print_u32_as_bytes(ysyx),my_id);

  /*
  int i = 0;
  for(i=0;i<4;i++){
    putch((ysyx>>((3-i)*8) & 0xffu));
  }
  putch('_');
  // 计算my_id的十进制位数
  uint32_t temp = my_id;
  int digits = 1;
  while (temp >= 10) {
    digits++;
    temp /= 10;
  }
  // 从高位到低位打印每一位
  for (i = digits - 1; i >= 0; i--) {
    uint32_t divisor = 1;
    for (int j = 0; j < i; j++) {
      divisor *= 10;
    }
    char num = (my_id / divisor) % 10;
    putch(48 + num);
  }
  putch('\n');
  */
  int ret = main(mainargs);
  halt(ret);
}
