/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include "../local-include/reg.h"
#include <utils.h>

#ifdef CONFIG_ETRACE
static void etrace_log_write(){
  log_write(ANSI_FMT("[ETRACE]\t" ,ANSI_FG_WHITE));
  log_write(ANSI_FMT("REG STATE\n" ,ANSI_FG_RED));
  log_write(ANSI_FMT("Mstatus: ",ANSI_FG_BLUE) "0x%08x\t",csr_read(ADDR_MSTATUS));
  log_write(ANSI_FMT("Mtvec  : ",ANSI_FG_BLUE) "0x%08x\n",csr_read(ADDR_MTVEC));
  log_write(ANSI_FMT("Mepc   : ",ANSI_FG_BLUE) "0x%08x\t",csr_read(ADDR_MEPC));
  log_write(ANSI_FMT("Mcause : ",ANSI_FG_BLUE) "0x%08x\n",csr_read(ADDR_MCAUSE));
}
#endif

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  csr_write(ADDR_MEPC ,epc);  
  csr_write(ADDR_MCAUSE ,NO);
  IFDEF(CONFIG_ETRACE, etrace_log_write());
  //printf("raise intr %x\n",csr(MTVEC));
  return csr(INDEX_MTVEC);
  }

word_t csr_read(paddr_t addr){
  switch(addr){
    case ADDR_MSTATUS:
      return csr(INDEX_MSTATUS);
    case ADDR_MTVEC:
      return csr(INDEX_MTVEC);
    case ADDR_MEPC:
      return csr(INDEX_MEPC);
    case ADDR_MCAUSE:
      return csr(INDEX_MCAUSE);
    default:
      printf("csr_read: unknown csr addr %x\n",addr);
  }
  return 0;
}

void csr_write(paddr_t addr, word_t data){
  switch(addr){
    case ADDR_MSTATUS:
      csr(INDEX_MSTATUS) = data;break;
    case ADDR_MTVEC:
      csr(INDEX_MTVEC) = data;break;
    case ADDR_MEPC:
      csr(INDEX_MEPC) = data;break;
    case ADDR_MCAUSE:
      csr(INDEX_MCAUSE) = data;break;
    default:
      printf("csr_write: unknown csr addr %x\n",addr);
  }
}


word_t isa_query_intr() {
  return INTR_EMPTY;
}

void init_csr(){
  csr_write(ADDR_MSTATUS ,0x1800u);
}
