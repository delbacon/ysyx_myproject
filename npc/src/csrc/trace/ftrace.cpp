#include <cpu/cpu.h>
#include <trace/ftrace.h>

//elf解析
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>

#ifdef CONFIG_FTRACE
//ftrace相关函数:
//============================================================================//
//elf文件的读取与函数名 & 对应地址的获取
//======================================//
//函数定义
// 加载 ELF 文件到内存（只读映射）
ElfFunction *func_list = NULL;
int func_num = 0;

static size_t count=0;



static int parse_elf64_functions_with_size(ElfFunction **out_funcs, char *elf_data) {
    //获取 elf 头部结构体
    //Elf32_Ehdr 描述了文件整体的布局信息
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)elf_data;
    //Elf32_Shdr 描述文件各节的具体内容和属性
    Elf64_Shdr *shdrs = (Elf64_Shdr *)((char *)elf_data + ehdr->e_shoff);

    //节头表的条目总数（节头表的每一个元素是一个Elf32_Shdr结构体）
    int shnum = ehdr->e_shnum;//用于遍历节头表

    ElfFunction *final = NULL;
    //capacity 存储函数的最大数量
    size_t capacity = 256;
    ElfFunction *funcs = (ElfFunction *)malloc(capacity * sizeof(ElfFunction));
    if (funcs == NULL) return -1;

    //遍历节头表
    for (int i = 0; i < shnum; i++) {
        //如果是静态符号表/动态符号表，就进一步读取相关数据
        if (shdrs[i].sh_type == SHT_SYMTAB || shdrs[i].sh_type == SHT_DYNSYM) {
            //指向符号表相关结构体
            Elf64_Sym *syms = (Elf64_Sym *)((char *)elf_data + shdrs[i].sh_offset);
            //符号表条目总数
            size_t sym_count = shdrs[i].sh_size / sizeof(Elf64_Sym);
            //获取字符串表
            char *strtab = (char *)elf_data + shdrs[shdrs[i].sh_link].sh_offset;

            for (size_t j = 0; j < sym_count; j++) {
                //如果字符串表某条目存储的是函数，并且函数名不为空，就记录到传入的函数列表中
                if (ELF64_ST_TYPE(syms[j].st_info) == STT_FUNC && syms[j].st_name != 0) {
                    const char *name_ptr = strtab + syms[j].st_name;
                    if (name_ptr[0] == '\0') continue;
                    word_t start = syms[j].st_value;
                    word_t size = syms[j].st_size;
                    word_t end = start + size;

                    // 跳过 size == 0 的函数
                    if (size == 0) continue;
                    //动态分配函数列表的大小
                    if (count >= capacity) {
                        capacity *= 2;
                        ElfFunction *tmp = (ElfFunction *)realloc(funcs, capacity * sizeof(ElfFunction));
                        if (!tmp) goto cleanup;
                        funcs = tmp;
                    }

                    char *name_copy = strdup(name_ptr);
                    if (!name_copy) goto cleanup;

                    funcs[count].name = name_copy;
                    funcs[count].start = start;
                    funcs[count].end = end;
                    funcs[count].size = size;
                    count++;
                }
            }
        }
    }

    if (count == 0) {
        free(funcs);
        *out_funcs = NULL;
        return 0;
    }

    //释放动态分配的内存（(ElfFunction *)realloc会尝试调用之前分配的内存块，如果size=0且对应位置已分配，则返回NULL）
    final = (ElfFunction *)realloc(funcs, count * sizeof(ElfFunction));
    if (!final) goto cleanup;
    *out_funcs = final;
    return count;

cleanup:
    for (size_t i = 0; i < count; i++) {
        free(funcs[i].name);
    }
    free(funcs);
    return -1;
}

static int parse_elf32_functions_with_size(ElfFunction **out_funcs, char *elf_data) {
    //获取 elf 头部结构体
    //Elf32_Ehdr 描述了文件整体的布局信息
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)elf_data;
    //Elf32_Shdr 描述文件各节的具体内容和属性
    Elf32_Shdr *shdrs = (Elf32_Shdr *)((char *)elf_data + ehdr->e_shoff);

    //节头表的条目总数（节头表的每一个元素是一个Elf32_Shdr结构体）
    int shnum = ehdr->e_shnum;//用于遍历节头表
    ElfFunction *final = NULL;
    //capacity 存储函数的最大数量
    size_t capacity = 256;
    ElfFunction *funcs = (ElfFunction *)malloc(capacity * sizeof(ElfFunction));
    if (funcs == NULL) return -1;

    //遍历节头表
    for (int i = 0; i < shnum; i++) {
        //如果是静态符号表/动态符号表，就进一步读取相关数据
        if (shdrs[i].sh_type == SHT_SYMTAB || shdrs[i].sh_type == SHT_DYNSYM) {
            //指向符号表相关结构体
            Elf32_Sym *syms = (Elf32_Sym *)((char *)elf_data + shdrs[i].sh_offset);
            //符号表条目总数
            size_t sym_count = shdrs[i].sh_size / sizeof(Elf32_Sym);
            //获取字符串表
            char *strtab = (char *)elf_data + shdrs[shdrs[i].sh_link].sh_offset;

            for (size_t j = 0; j < sym_count; j++) {
                //如果字符串表某条目存储的是函数，并且函数名不为空，就记录到传入的函数列表中
                if (ELF32_ST_TYPE(syms[j].st_info) == STT_FUNC && syms[j].st_name != 0) {
                    const char *name_ptr = strtab + syms[j].st_name;
                    if (name_ptr[0] == '\0') continue;
                    word_t start = syms[j].st_value;
                    word_t size = syms[j].st_size;
                    word_t end = start + size;

                    // 跳过 size == 0 的函数
                    if (size == 0) continue;
                    //动态分配函数列表的大小
                    if (count >= capacity) {
                        capacity *= 2;
                        ElfFunction *tmp = (ElfFunction *)realloc(funcs, capacity * sizeof(ElfFunction));
                        if (!tmp) goto cleanup;
                        funcs = tmp;
                    }

                    char *name_copy = strdup(name_ptr);
                    if (!name_copy) goto cleanup;

                    funcs[count].name = name_copy;
                    funcs[count].start = start;
                    funcs[count].end = end;
                    funcs[count].size = size;
                    count++;
                }
            }
        }
    }

    if (count == 0) {
        free(funcs);
        *out_funcs = NULL;
        return 0;
    }

    //释放动态分配的内存（(ElfFunction *)realloc会尝试调用之前分配的内存块，如果size=0且对应位置已分配，则返回NULL）
    final = (ElfFunction *)realloc(funcs, count * sizeof(ElfFunction));
    if (!final) goto cleanup;
    *out_funcs = final;
    return count;

cleanup:
    for (size_t i = 0; i < count; i++) {
        free(funcs[i].name);
    }
    free(funcs);
    return -1;
}

static int parse_elf_functions_with_size(ElfFunction **out_funcs, char *elf_data) {
    //如果没有读到elf文件，或者函数指针为空，则返回-1
    if (!elf_data) {
        return -1;
    }
    //指向 elf 文件头部标识部分的指针
    unsigned char *e_ident = (unsigned char *)elf_data;
    //检测读取的文件是否为 elf32 文件
    
    if (memcmp(e_ident, ELFMAG, SELFMAG) != 0 ) return -1;

    if(e_ident[EI_CLASS] == ELFCLASS32) {
        Log("ELF32\n");
        return parse_elf32_functions_with_size(out_funcs, elf_data);
    }else if(e_ident[EI_CLASS] == ELFCLASS64){
        Log("ELF64\n");
        return parse_elf64_functions_with_size(out_funcs, elf_data);
    }
    return -1;
}
static void free_elf_functions(ElfFunction *funcs) {
    if (!funcs) return;
    for (int i = 0; i < count; i++) {
        free(funcs[i].name);
    }
    free(funcs);
}

static int init_elf_file(const char *elf_file)  {
    if (elf_file==NULL) return -1;

    printf("init elf file: %s\n",elf_file);
    int fd = open(elf_file, O_RDONLY);
    if (fd < 0) {
        printf("open %s failed\n", elf_file);
        perror("open");
        return -1;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("fstat");
        close(fd);
        return -1;
    }

    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd); // 可立即关闭 fd，mmap 已持有引用
    if (map == MAP_FAILED) {
        perror("mmap");
        return -1;
    }
    char *elf_data = (char *)map;
    func_num = parse_elf_functions_with_size(&func_list, elf_data);
    printf("parse elf file success, func_num: %d\n", func_num);
    return 0;
}

//======================================//


static int call_depth = 0;
static char *ftrace_get_func_name(vaddr_t pc){
    if (func_num < 0) {
        return NULL;
    } else {
        int func_start = 0;
        int func_end = 0;
        for (int i = 0; i < func_num; i++) {
            func_start = func_list[i].start;
            func_end = func_list[i].end;
            if(pc >= func_start && pc < func_end){
                return func_list[i].name;
            }
        }
    }
    printf("can not find function name for pc: %08x\n", pc);
    return NULL;
    
}
void ftrace_call(vaddr_t pc, vaddr_t pc_target){ 
    call_depth++;
    //if (call_depth <= 2) return; // ignore _trm_init & main
    log_write(ANSI_FMT(FMT_PADDR":",ANSI_BG_BLUE),pc);

    log_write(ANSI_BG_CYAN);
#ifdef CONFIG_FTRACE_INDENT
    log_write("%*s",(call_depth)*2, "");
#else
    log_write("f%d_",call_depth);
#endif

    log_write("call [%s@" FMT_PADDR "]" ANSI_NONE "\n",
		ftrace_get_func_name(pc_target),pc_target);
}

void ftrace_ret(vaddr_t pc){
    //if (call_depth <= 2) return; // ignore _trm_init & main

    log_write(ANSI_FMT(FMT_PADDR":",ANSI_BG_YELLOW),pc);

    log_write(ANSI_BG_GREEN);
#ifdef CONFIG_FTRACE_INDENT
    log_write("%*s",(call_depth)*2, "");
#else
    log_write("f%d_",call_depth);
#endif
    log_write("ret [%s]" ANSI_NONE "\n",ftrace_get_func_name(pc));
    call_depth--;
}

int init_ftrace(const char *elf_file){
    return init_elf_file(elf_file);
}

void ftrace_free(ElfFunction *funcs)
{
    free_elf_functions(funcs) ;
}
#endif
//============================================================================//
