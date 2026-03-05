#include "../../include/device.h"

int device_read(uint32_t addr)
{
    if(addr < MMIO_BASE || addr > MMIO_END) return -1;
    
    //read rtc
    if(addr >= RTC_MMIO_START && addr < RTC_MMIO_END){
        return rtc_read(addr);
    }else{
        
    }
    return -1;
}

int device_write(uint32_t addr, uint32_t wdata)
{
    if(addr == COM_MMIO_START) { 
        putchar((uint8_t)(wdata & 0xffu));
    return 0;
    }
    return -1; 
}

void device_init()
{
    rtc_init();
}