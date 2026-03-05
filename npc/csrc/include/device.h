#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "common.h"
#include "cpu.h"

//---------- device addr ----------//
#define MMIO_BASE 0x10000000
#define COM_MMIO_START  (MMIO_BASE + 0x0000000)
#define RTC_MMIO_START  (MMIO_BASE + 0x0000048)
#define RTC_MMIO_END    (RTC_MMIO_START + 32)
#define MMIO_END        (MMIO_BASE + 0x00001000)



// ---------- clock.c ------------//

uint64_t get_time_us();

int rtc_read(uint32_t vraddr);


void rtc_init();




// ---------- device.c ------------//
int device_read(uint32_t addr);

int device_write(uint32_t addr, uint32_t wdata);

void device_init();






#endif