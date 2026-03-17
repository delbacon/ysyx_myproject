#include <am.h>
#include <nemu.h>

#include <klib.h>
#include <klib-macros.h>

extern char _heap_start;
int main(const char *args);

Area heap = RANGE(&_heap_start, PMEM_END);
static const char mainargs[MAINARGS_MAX_LEN] = TOSTRING(MAINARGS_PLACEHOLDER); // defined in CFLAGS

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  nemu_trap(code);

  // should not reach here
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

  int ret = main(mainargs);
  halt(ret);
}
