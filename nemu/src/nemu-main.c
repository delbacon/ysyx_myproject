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

#include <common.h>

#include "monitor/sdb/sdb.h"


void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();


int main(int argc, char *argv[]) {
  // Initialize the monitor. //

#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  // Start engine. //
  engine_start();

  return is_exit_status_bad();
}

/*

//test_expr

int main(int argc, char *argv[]) {
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  // Start engine. //
  engine_start();
  // 跳过 NEMU monitor 初始化
  const char *input_file = "/home/delbacon/ysyx-workbench/nemu/tools/gen-expr/input";
  FILE *fp = fopen(input_file, "r");
  if (!fp) {
    fprintf(stderr, "Error: cannot open input file '%s'\n", input_file);
    return 1;
  }

  char line[65536];
  int passed = 0, total = 0;

  while (fgets(line, sizeof(line), fp)) {
    // 找到第一个空格，分割期望结果和表达式
    char *space = strchr(line, ' ');
    if (!space) {
      fprintf(stderr, "Invalid line (no space): %s", line);
      continue;
    }



    // 提取期望结果
    *space = '\0'; // 分割字符串
    uint32_t expected = strtoul(line, NULL, 10);

    // 表达式从 space + 1 开始，跳过前导空格
    char *expr_str = space + 1;
    while (*expr_str == ' ' || *expr_str == '\t') expr_str++;
    if (*expr_str == '\0') {
      fprintf(stderr, "Empty expression: %s\n", line);
      continue;
    }
    
    // 去掉末尾换行符（如果存在）
    char *nl = strchr(expr_str, '\n');
    if (nl) *nl = '\0';
    nl = strchr(expr_str, '\r');
    if (nl) *nl = '\0';

    total++;
    bool success = true;
    uint32_t actual = expr(expr_str, &success);

    if (actual == expected) {
      passed++;
      //printf("PASS: %s\n", expr_str); // 可选：打印通过的
    } else {
      printf("FAIL: expected=%u, got=%u, expr=%s\n",
             expected, actual , expr_str);
      if (!success) {
        printf("  -> Evaluation failed (e.g., div-by-zero or syntax error)\n");
      }
    }
  }

  fclose(fp);
  printf("\n[Summary] %d/%d tests passed.\n", passed, total);

  return (passed == total) ? 0 : 1;
}
*/