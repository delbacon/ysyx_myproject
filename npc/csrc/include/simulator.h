#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__ 


#include "common.h"

#include <verilated.h>
#include <verilated_fst_c.h>
#include <Vysyx_26020055_top.h>
#include <iostream>

//DPI-C
#include "svdpi.h"
#include "Vysyx_26020055_top__Dpi.h"

#include "memory.h"
#include "device.h"
#include "utils.h"
#include "trace.h"
#include "cpu.h"

void exec_once();

void execute(uint64_t n);

int cpu_exec(uint64_t n);

void simulator(int argc, char** argv);

void simulator_init(int argc, char** argv);


#endif