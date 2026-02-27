#include "readbin.h"

// 加载 RISC-V32 指令二进制文件到内存
// 返回: 指向 uint32_t 数组的指针（每项是一条指令）
//       *count = 指令条数
//       调用者负责 free()
extern "C" uint32_t *load_riscv32_instructions(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    // 检查是否为 4 的倍数
    if (file_size % 4 != 0) {
        fprintf(stderr, "Error: file size (%ld) is not a multiple of 4\n", file_size);
        fclose(fp);
        return NULL;
    }

    size_t num_instructions = (size_t)file_size / 4;
    uint32_t *instructions = static_cast<uint32_t*>(malloc(file_size * 2));  // 分配原始字节空间

    if (!instructions) {
        perror("malloc");
        fclose(fp);
        return NULL;
    }

    // 读取整个文件（原始字节流）
    size_t bytes_read = fread(instructions, 1, (size_t)file_size, fp);
    fclose(fp);

    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Error: only read %zu of %ld bytes\n", bytes_read, file_size);
        free(instructions);
        return NULL;
    }

    // ✅ 关键点：由于 RISC-V 和主机都是小端，
    //    内存中的字节布局 [b0, b1, b2, b3] 自动解释为 0x b3 b2 b1 b0（小端）
    //    但 fread 读入的就是 [b0, b1, b2, b3]，而 *(uint32_t*) 会按小端解释为 0xb3b2b1b0
    //    这正是 RISC-V 指令的正确值。
    //    所以无需手动转换！

//    *count = num_instructions;
    return instructions;  // 每个元素是一条 32 位指令
}
