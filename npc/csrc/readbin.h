#ifndef __READBIN_H__
#define __READBIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_LINE_LENGTH 10000

extern "C" uint32_t *load_riscv32_instructions(const char *filename) ;

#endif

/*
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <riscv32_instructions.bin>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t count;
    uint32_t *instrs = load_riscv32_instructions(argv[1], &count);
    if (!instrs) {
        return EXIT_FAILURE;
    }

    printf("Loaded %zu RISC-V32 instructions:\n", count);
    for (size_t i = 0; i < count && i < 10; i++) {  // 打印前10条
        printf("instr[%zu] = 0x%08X\n", i, instrs[i]);
    }

    // 示例：第一条指令解码（可选）
    // uint32_t first = instrs[0];
    // 可在此添加反汇编逻辑

    free(instrs);
    return EXIT_SUCCESS;
}

*/
