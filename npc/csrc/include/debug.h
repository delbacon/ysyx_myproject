#ifndef __DEBUG_H__
#define __DEBUG_H__ 

#include <assert.h>

#define panic(format, ...)  printf(format, ##__VA_ARGS__);\
                            assert(0);

#endif