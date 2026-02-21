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

#include "sdb.h"


typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  word_t old;
  char expr[256];
  /* TODO: Add more members if necessary */

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

static WP* new_wp() 
{
  //如果还有空位置的话
  assert(free_!=NULL);
  WP* ret = free_;
  free_ = free_->next;
  ret->next = head;
  head = ret;
  return ret;
}

static void free_wp(WP *wp)
 {
  WP* h = head;
  if (h == wp) head = wp->next;
  else {
    while (h != NULL && h->next != wp) h = h->next;
    assert(h!=NULL);
    h->next = wp->next;
  }
  wp->next = free_;
  free_ = wp;
}


//监视某个地址的数据
void wp_watch(char *expr, word_t res) 
{
  WP* wp = new_wp();
  strcpy(wp->expr, expr);
  wp->old = res;
  printf("Wp %d: %s\n", wp->NO, expr);
}


//移除某一个wp
void remove_wp(int no) {
  assert(no < NR_WP);
  WP* wp = &wp_pool[no];
  free_wp(wp);
  printf("Delete wp %d: %s\n", wp->NO, wp->expr);
}

void wp_difftest() {
  WP* h = head;
  while (h) {
    bool success;
    word_t new = expr(h->expr, &success);
    //如果存储的值发生变化，执行
    if (h->old != new) {
      printf("Wp %d: %s\n"
        "Old value = %u 0x%x\n"
        "New value = %u 0x%x\n"
        , h->NO, h->expr, h->old, h->old, new, new);
      h->old = new;
      //暂停运行
      nemu_state.state = NEMU_STOP;
      return ;
    }
    h = h->next;
  }
  return ;
}
void wp_display() {
  WP* h = head;
  if (h==NULL) {
    printf("No wp.\n");
    return;
  }
  printf("%-4s  %-4s  %-4s\n", "Num", "Wp", "Result");
  while (h) {
    printf("%-4d  %-4s  0x%-8x\n", h->NO, h->expr, h->old);
    h = h->next;
  }
}
