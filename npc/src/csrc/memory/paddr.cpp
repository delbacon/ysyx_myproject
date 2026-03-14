#include <memory/host.h>
#include <memory/paddr.h>
#include <device/mmio.h>
#include <trace/mtrace.h>
#include <cpu/isa.h>

static uint8_t *pROM = NULL;
static uint8_t *pRAM = NULL ;
//for pROM
uint8_t* pROM_guest_to_host(paddr_t paddr) { return pROM + paddr - CONFIG_MBASE; }

//for pRAM
uint8_t* guest_to_host(paddr_t paddr) { return pRAM + paddr - CONFIG_MBASE; }
paddr_t host_to_guest(uint8_t *haddr) { return haddr - pRAM + CONFIG_MBASE; }

//pc_pROM
//===================================================//
static word_t pc_pmem_read(paddr_t addr) {
    // pc 读指令每次必定 4 byte（32bit）
    word_t ret = host_read(pROM_guest_to_host(addr), 4);
    //printf("addr:%x inst:%x\n",addr,ret);
    return ret;
}
//===================================================//



//pRAM
//===================================================//
static word_t pmem_read(paddr_t addr, int len) {
	word_t ret = host_read(guest_to_host(addr), len);
	IFDEF(CONFIG_MTRACE,mtrace_read(addr, len, ret);)

	return ret;
}

static void pmem_write(paddr_t addr, int len, word_t data) {
	host_write(guest_to_host(addr), len, data);

	IFDEF(CONFIG_MTRACE,mtrace_write(addr, len, data);)

}

static void out_of_bound(paddr_t addr) {
    if(addr == 0x0) return ;
    panic("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR ", " FMT_PADDR "] at pc = " FMT_WORD,
        addr, PMEM_LEFT, PMEM_RIGHT, cpu.pc);
}
//===================================================//

uint8_t *load_riscv32_instructions(const char *filename, uint8_t *buffer, size_t buffer_size) {
   FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    // 检查是否为 4 的倍数（可选，保留语义检查）
    
    if (file_size % 4 != 0) {
        fprintf(stderr, "Error: file size (%ld) is not a multiple of 4\n", file_size);
        fclose(fp);
        return NULL;
    }
    
    // 检查缓冲区是否足够大
    if ((size_t)file_size > buffer_size) {
        fprintf(stderr, "Error: file size (%ld) exceeds buffer size (%zu)\n", file_size, buffer_size);
        fclose(fp);
        return NULL;
    }

    // 读取整个文件到提供的缓冲区
    size_t bytes_read = fread(buffer, 1, (size_t)file_size, fp);
    fclose(fp);

    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Error: only read %zu of %ld bytes\n", bytes_read, file_size);
        return NULL;
    }

    // 将剩余内存初始化为0
    if (bytes_read < buffer_size) {
        memset(buffer + bytes_read, 0, buffer_size - bytes_read);
    }

    return buffer;  // 返回缓冲区指针
}

// mem_ctrl API:
//===================================================//
void init_mem(char *file)
{
  if (file == nullptr) {
    printf("Error: No image file specified!\n");
    exit(1);
  }
  
    // 分配页对齐的内存
    if (posix_memalign((void**)&pROM, 4096, CONFIG_MSIZE) != 0) {
        perror("Failed to allocate aligned memory for pROM");
        exit(1);
    }
    
    if (posix_memalign((void**)&pRAM, 4096, CONFIG_MSIZE) != 0) {
        perror("Failed to allocate aligned memory for pRAM");
        exit(1);
    }

    // 初始化 RAM & ROM
    printf("%s\n",file);
    if (load_riscv32_instructions(file, pROM, CONFIG_MSIZE) == NULL) {
        perror("Failed to load instructions to pROM");
        exit(1);
    }
    if (load_riscv32_instructions(file, pRAM, CONFIG_MSIZE) == NULL) {
        perror("Failed to load instructions to pRAM");
        exit(1);
    }
    Log("physical memory area [" FMT_PADDR ", " FMT_PADDR "]", PMEM_LEFT, PMEM_RIGHT);
}


word_t pROM_read(paddr_t addr) {
  if (likely(in_pmem(addr))) return pc_pmem_read(addr);
  out_of_bound(addr);
  return 0;
}
int pROM_read_HDL(int addr) {
  return (int)pROM_read((paddr_t)addr);
}

word_t pRAM_read(paddr_t addr, int len) {
  if (likely(in_pmem(addr))) return pmem_read(addr, len);
  return mmio_read(addr, len);
  out_of_bound(addr);
  return 0;
}
int pRAM_read_HDL(int addr, int len) {
  return (int)pRAM_read((paddr_t)addr, len);
}


void pRAM_write(paddr_t addr, int len, word_t data) {
  if (likely(in_pmem(addr))) { pmem_write(addr, len, data); return; }
  mmio_write(addr, len, data); return;
  out_of_bound(addr);
}
void pRAM_write_HDL(int addr, int len, int data) {
  pRAM_write((paddr_t)addr, len, (word_t)data);
}


void free_pmem()
{
	if(pROM) free(pROM);
	if(pRAM) free(pRAM);
  pROM = NULL;
  pRAM = NULL;
}

//===================================================//
