#include <device/map.h>
#include <utils.h>
#include <time.h>

static uint32_t *rtc_port_base = NULL;

static uint64_t time_start=0;

uint64_t get_time_us() {
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
        return 0; // 失败
    }
    return ((uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)(ts.tv_nsec / 1000)) - time_start;
}

//创建了 8 个 regs ，用来存储 rtc 相关的数据
//具体布局：
static void rtc_io_handler(uint32_t offset, int len, bool is_write) {

  assert(offset % 4 == 0 || offset <= 4*8);
  if (!is_write && (offset == 0 || offset == 4*2)) {	// 每次读取 us[31:0] 的时候会刷新整所有 rtc 相关寄存器
    time_t now;
    time(&now);
    struct tm *local_tm = localtime(&now);
	  uint64_t us = get_time_us();
    // 3. 提取各部分到 int 变量
    rtc_port_base[0] = (uint32_t)(us & 0xffffffffu);
    rtc_port_base[1] = (us >> 32);
    rtc_port_base[2] = local_tm->tm_sec;        
    rtc_port_base[3] = local_tm->tm_min;        
    rtc_port_base[4] = local_tm->tm_hour;       
    rtc_port_base[5] = local_tm->tm_mday;       
    rtc_port_base[6] = local_tm->tm_mon + 1;    
    rtc_port_base[7] = local_tm->tm_year + 1900;
  }
}



void init_rtc() {
	int space = NEW_IO_SPACE(8);
  	rtc_port_base = (uint32_t *)new_space(space);//32bit * 2 reg / 8 in one addr

  	add_mmio_map("rtc", CONFIG_RTC_MMIO, rtc_port_base, space, rtc_io_handler);	
  
	  time_start = get_time_us();
  //add_alarm_handle(timer_intr);
}

