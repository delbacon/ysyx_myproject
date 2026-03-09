#ifndef __MTRACE_H__
#define __MTRACE_H__ 


void mtrace_write(paddr_t addr, int len, word_t data);
void mtrace_read(paddr_t addr, int len, word_t data);

#endif