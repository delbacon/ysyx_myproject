#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <trace/itrace.h>
#ifdef CONFIG_ITRACE
//itrace 相关函数:
//============================================================================//
//换行缓冲区的实现
static ring_buffer_t *cb=NULL;

static void ring_buffer_init(){
  cb = (ring_buffer_t *)malloc(sizeof(ring_buffer_t));
  cb->head = 0;
  cb->tail = 0;
  cb->cnt  = 0;
  for(int i = 0; i < RING_BUFFER_SIZE; i++){
    cb->buf[i][0] = '\0';
  }
}

static int ring_buffer_put(char *c){ 
  if(cb->head >= RING_BUFFER_SIZE){
    return -1;
  }else{
    for(int i=0; i<128; i++){
      cb->buf[cb->head][i] = c[i];
    }
    cb->head = (cb->head + 1) % RING_BUFFER_SIZE;
    cb->cnt ++;
    return 0;
  }
}

void itrace_log_write(){
    log_write("\t\t\t  " ANSI_FMT("The lastest %d INSTs", ANSI_BG_BLUE) "\n",
     RING_BUFFER_SIZE);

    int index = cb->head;
    //如果缓冲区被写满，就从最新写入的单元+1开始输出
    if(cb->cnt > RING_BUFFER_SIZE)
        for(int i = index-1; ((i-index) % RING_BUFFER_SIZE) < RING_BUFFER_SIZE ; i++){
          if(cb->buf[i][0] == '\0') break;
          log_write("%03d: %s\n",(i-index+1), cb->buf[(i+1) % RING_BUFFER_SIZE]);
          cb->cnt-- ;
        } 
    //否则从头开始输出
    else {
      for(int i = 0; i < index; i++){
        if(cb->buf[i][0] == '\0') break;
        log_write("%03d: %s\n",i , cb->buf[i]);
      }
    }
    log_write("\t\t\t  %s\n", ANSI_FMT("INST STOP", ANSI_BG_RED));
  //这里的_this->logbuf存储的是向log写入的数据，默认是执行的 inst 和 pc ,每次执行的时候都会往里面写内容
}

//这里是实现 ITRACE 的功能，logbuf 是 log 缓存器
//先把缓存器的地址赋给 p ，再对 p 进行一些操作
//============================================================================//
void itrace_list_write(Decode *s){
  char *p = s->logbuf;
  p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);
  int ilen = s->snpc - s->pc;
  int i;
  //先取地址再取内容，这样取到的是第一个字节的数据，并且可以通过指针访问后续字节
  //如果直接强制类型转换为uint8_t,会丢失第一个字节后的内容
  uint8_t *inst = (uint8_t *)&s->isa.inst;
  //这里特殊处理x86是因为指令顺序不同
#ifdef CONFIG_ISA_x86
  for (i = 0; i < ilen; i ++) 
#else
  for (i = ilen - 1; i >= 0; i --) 
#endif
  {
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;

  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst, ilen);

}

int itrace_list_put(char *c){
    return ring_buffer_put(c);
}

void itrace_list_init(){
    ring_buffer_init();
}
#endif
//============================================================================//

