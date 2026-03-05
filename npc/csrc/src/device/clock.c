#include "../../include/device.h"  
#include <time.h>

static uint64_t time_start=0;
uint64_t get_time_us() {
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
        return 0; // 失败
    }
    return (uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)(ts.tv_nsec / 1000);
}

int rtc_read(uint32_t vraddr){
    if(vraddr >= RTC_MMIO_START && vraddr < RTC_MMIO_END){
    	time_t now;
    	time(&now);
    	struct tm *local_tm = localtime(&now);
    	uint32_t res;
    	// 3. 提取各部分到 int 变量
    	uint32_t year  = local_tm->tm_year + 1900;  // tm_year 是从 1900 年开始的偏移
    	uint32_t month = local_tm->tm_mon + 1;      // tm_mon 范围是 0~11，所以 +1
    	uint32_t day   = local_tm->tm_mday;         // 1~31
    	uint32_t hour  = local_tm->tm_hour;         // 0~23
    	uint32_t min   = local_tm->tm_min;          // 0~59
    	uint32_t sec   = local_tm->tm_sec;          // 0~61（考虑闰秒）
    	if (vraddr == RTC_MMIO_START){
    	  res = (uint32_t)(get_time_us() - time_start);return res;
    	}else if(vraddr == (RTC_MMIO_START + 4)){
    	  res = (uint32_t)((get_time_us() - time_start) >> 32);return res;
    	}else if(vraddr == RTC_MMIO_START + 8){
    	  res = sec;return res;
    	}else if(vraddr == RTC_MMIO_START + 12){
    	  res = min;return res;
    	}else if(vraddr == RTC_MMIO_START + 16){
    	  res = hour;return res;
    	}else if(vraddr == RTC_MMIO_START + 20){
    	  res = day;return res;
    	}else if(vraddr == RTC_MMIO_START + 24){
    	  res = month;return res;
    	}else if(vraddr == RTC_MMIO_START + 28){
    	  res = year;return res;
    	}
	}
    return -1;
}

void rtc_init(void)
{
  time_start = get_time_us();
}