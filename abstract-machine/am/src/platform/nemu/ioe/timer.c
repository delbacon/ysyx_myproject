#include <am.h>
#include <nemu.h>
#include <klib.h>
void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
//这里会调用nemu的timer.c的rtc_io_handler函数获取时间，要注意原始状态下的rtc_io_handler是在读取高位时才更新
//要不这里先读高位，要不修改rtc_io_handler，使得读取低位时更新
//调用链  地址获取： am 下的 src/riscv/riscv.h/inl -> ./ioe.c/ioe_read  
//       数值填充： nemu 下的 device/timer.c/add_mmio_map("rtc", CONFIG_RTC_MMIO, rtc_port_base, 8, rtc_io_handler);
//                会分配对应地址范围给变量rtc_port_base,并通过callback函数指针,实现当对应mem区域被访问时，执行函数rtc_io_handler
  uint32_t time_us_l = inl(RTC_ADDR);       
  uint32_t time_us_h = inl(RTC_ADDR+4);

//  printf("time_us_l = %d  time_us_h = %d\n", time_us_l, time_us_h);
  uptime->us = ((uint64_t)time_us_h << 32) | (uint64_t)time_us_l;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
