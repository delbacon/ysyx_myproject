#include "mem_load.h"
#define _EBREAK
#include "mem_load.h"
#define _EBREAK
extern "C" uint32_t* read_to_MEM(const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("无法打开文件");
        return NULL;
    }

    // 预分配足够大的空间（注意：实际可考虑动态扩容）
    size_t max_words = 40000 * 8;
    uint32_t *ROM = static_cast<uint32_t*>(calloc(max_words, sizeof(uint32_t))); // 使用calloc初始化为0
    if (ROM == NULL) {
        fclose(fp);
        fprintf(stderr, "内存不足\n");
        return NULL;
    }

    int count = 0;
    char line[10000];

    while (fgets(line, sizeof(line), fp) != NULL && count < (int)max_words) {
        char *token = strtok(line, " \t\r\n:");
        while (token != NULL && count < (int)max_words) {
            if (strlen(token) == 8 && isxdigit((unsigned char)token[0])) {
                ROM[count] = strtoul(token, NULL, 16);
                count++;
            }
            token = strtok(NULL, " \t\r\n:");
        }
    }

#ifdef _EBREAK
    if (strcmp(fname, "./resources/sum.hex") == 0) {
        if ((0x228 >> 2) < max_words) {
            ROM[(0x228 >> 2)] = 0x00100073;   // ebreak at 0x228
        }
    } else if (strcmp(fname, "./resources/mem.hex") == 0) {
        if ((0x1220 >> 2) < max_words) {
            ROM[(0x1220 >> 2)] = 0x00100073;  // ebreak at 0x1220
        }
    }
#endif

    printf("成功读取 %d 个十六进制数\n", count);
    for (int i = 0; i < (count > 10 ? 10 : count); i++) {
        printf("ROM[%d] = 0x%08x (%u)\n", i, ROM[i], ROM[i]);
    }
    if (count > 40000) {
        printf("ROM[%d] = 0x%08x (%u)\n", 40000, ROM[40000], ROM[40000]);
    }
    fclose(fp);

    return ROM;
}


/*
e.g:
uint32_t *pROM = NULL;
uint32_t *pRAM = NULL;

int main(int argc, char *argv[])
{
	read_to_ROM(pROM,argv[1]);
	read_to_RAM(pRAM,argv[2]);

    ....

	free_mem();

	return 0;
}
*/