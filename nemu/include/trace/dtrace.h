#ifndef __DTRACE_H__
#define __DTRACE_H__ 

#include <common.h>
#include <device/map.h>

void dtrace_read(vaddr_t addr, word_t ret, IOMap *map);
void dtrace_write(vaddr_t addr, int len , word_t data, IOMap *map);

#endif