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


/*
//pmemread
//偏移地址是0x80000000，但是初始化的时候有一小会会回到0，这里是为了防止越界
  uint32_t raddr = 0 ;
  if(vraddr >= 0x80000000) raddr = vraddr - 0x80000000;

  // 总是读取地址为`raddr & ~0x3u`的4字节返回
  uint32_t offset = raddr & 0x3;
  uint32_t res = 0;
  //实现外设的访问
//-----------------------------------------------------------------------------------------//
  if(vraddr >= MMIO_BASE && vraddr < MMIO_END){
    uint32_t res = device_read(vraddr);

#ifdef CONFIG_DTRACE
    if(raddr >=CONFIG_DTRACE_START && raddr < CONFIG_DTRACE_END){
      word_t tmp_array[4];
      for(int i=0;i<4;i++){
        tmp_array[i] = (res & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
      }
      log_write(ANSI_FMT("[DEV]",ANSI_FG_WHITE) 
                ANSI_FMT("[READ ] ",ANSI_FG_RED) 
                ANSI_FMT(FMT_PADDR": ",ANSI_FG_MAGENTA), vraddr);
      for(int i=0;i<4;i++){
        log_write("%02x ", tmp_array[i] );
      }
      log_write(ANSI_FMT("[%s]",ANSI_FG_GREEN), device_get_name((word_t)vraddr));
      log_write("\n");
    }
#endif

    return res;
  }else if(vraddr >= PMEM_LEFT && vraddr < PMEM_RIGHT){

  // 实现内存的访问
//-----------------------------------------------------------------------------------------//
  res = ((uint64_t)(cpu.pRAM[(raddr >> 2)+4]) <<  8 * (4 - offset)) | (cpu.pRAM[raddr >> 2] >> (offset * 8)) ;
#ifdef CONFIG_MTRACE
    if(vraddr >=CONFIG_MTRACE_START && vraddr < CONFIG_MTRACE_END){
      word_t tmp_array[4];
      for(int i=0;i<4;i++){
        tmp_array[i] = (res & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
      }
      log_write(ANSI_FMT("[MEM]",ANSI_FG_GREEN) 
                ANSI_FMT("[READ ] ",ANSI_FG_RED) 
                ANSI_FMT(FMT_PADDR": ",ANSI_FG_MAGENTA), vraddr);
      for(int i=0;i<4;i++){
        log_write("%02x ", tmp_array[i] );
      }
      log_write("\n");
    }
#endif
//-----------------------------------------------------------------------------------------//
    return res;
  }
  return -1;

#ifdef CONFIG_DTRACE
    if(vwaddr >=CONFIG_DTRACE_START && vwaddr < CONFIG_DTRACE_END){
      word_t tmp_array[4];
      for(int i=0;i<4;i++){
        tmp_array[i] = (wdata & (0xff000000u >> (8 * i)) ) >> (8 * (3-i));
      }
      log_write(ANSI_FMT("[DEV]",ANSI_FG_WHITE) 
                ANSI_FMT("[WRITE] ",ANSI_FG_BLUE) 
                ANSI_FMT(FMT_PADDR": ",ANSI_FG_CYAN), vwaddr);
      for(int i=0;i<4;i++){
        log_write("%02x ", tmp_array[i] );
      }
      log_write("wmask:%c", wmask);
      log_write(ANSI_FMT("[%s]",ANSI_FG_GREEN), device_get_name((word_t)vwaddr));
      log_write("\n");
    }
#endif

  uint32_t waddr = 0 ;
  if(vwaddr >= 0x80000000) waddr = vwaddr - 0x80000000;

  uint32_t offset = waddr & 0x3;
  uint32_t mask_off;
  switch (wmask)
  {
  case 1:
      mask_off = 0x000000ffu << (offset * 8);
      cpu.pRAM[waddr >> 2] = (cpu.pRAM[waddr >> 2] & ~mask_off) | (wdata & 0xffu) << (offset * 8);
    break;
  case 2:
      mask_off = 0x0000ffffu << (offset * 8);
      cpu.pRAM[waddr >> 2] = (cpu.pRAM[waddr >> 2] & ~mask_off) | (wdata & 0xffffu) << (offset * 8);
    break;
  case 4:
      cpu.pRAM[waddr >> 2] = wdata;
    break;
  
  default:
	break;
  }
#ifdef CONFIG_MTRACE
  if(waddr >=CONFIG_MTRACE_START && waddr < CONFIG_MTRACE_END){
    word_t tmp_array[8];
    for(int i=0;i<sizeof(word_t);i++){
      tmp_array[i] = (wdata & (~0xffu >> (8 * i)) ) >> (8 * (3-i));
    }
    log_write(ANSI_FMT("[MEM]",ANSI_FG_GREEN) 
              ANSI_FMT("[WRITE] ",ANSI_FG_BLUE) 
              ANSI_FMT(FMT_PADDR": ",ANSI_FG_CYAN), waddr);
    for(int i=0;i<4;i++){
      log_write("%02x ", tmp_array[i] );
    }
    log_write("wmask:%c\n",wmask);
  }
#endif

}
  */