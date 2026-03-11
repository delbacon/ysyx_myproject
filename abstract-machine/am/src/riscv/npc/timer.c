#include <am.h>
#include <riscv/riscv.h>

#define RTC_ADDR        (0x10000000 + 0x00000048)

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t time_us_l = inl(RTC_ADDR);       
  uint32_t time_us_h = inl(RTC_ADDR+4);
  uptime->us = ((uint64_t)time_us_h << 32) | (uint64_t)time_us_l;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  uint32_t time_s = inl(RTC_ADDR+8);
  uint32_t time_min = inl(RTC_ADDR+12);
  uint32_t time_h = inl(RTC_ADDR+16);
  uint32_t time_d = inl(RTC_ADDR+20);
  uint32_t time_m = inl(RTC_ADDR+24);
  uint32_t time_y = inl(RTC_ADDR+28);
  rtc->second = time_s;
  rtc->minute = time_min;
  rtc->hour   = time_h;
  rtc->day    = time_d;
  rtc->month  = time_m;
  rtc->year   = time_y;
}