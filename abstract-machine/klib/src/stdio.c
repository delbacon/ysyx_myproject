#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}


static void int2str(char *str, int num) {
  int negative = 0;
  char buf[32];
  
  // 处理负数情况，特别注意INT_MIN的边界条件
  if (num < 0) {
    negative = 1;
    // 避免INT_MIN溢出，直接处理特殊情况
    if (num == -2147483648) {
      // INT_MIN的绝对值无法用int表示，特殊处理
      strcpy(buf, "-2147483648");
      strcpy(str, buf);
      return;
    }
    num = -num;
  }

  int cnt = 0;
  int temp_num = num; // 使用临时变量避免修改原始num
  
  // 计算数字位数
  do {
    cnt++;
    temp_num /= 10;
  } while (temp_num > 0);

  buf[cnt + negative] = '\0'; // 为负号预留空间
  
  // 填充数字字符
  temp_num = num; // 重新初始化临时变量
  for (int i = cnt - 1 + negative; i >= negative; i--) {
    buf[i] = '0' + temp_num % 10;
    temp_num /= 10;
  }

  // 添加负号（如果需要）
  if (negative) {
    buf[0] = '-';
  }
  
  // 复制到目标字符串
  strcpy(str, buf);
}

int vsprintf(char *out, const char *fmt, va_list ap) {

  char *start = out;
  char buf[32];

  while(*fmt){
    switch(*fmt){
      case '%': 
        fmt++;
        switch(*fmt){
          case 'c': {
            char c = va_arg(ap, int);
            *out++ = c;
            break;
          }
          case 'd': {
              int num = va_arg(ap, int);
              // 将整数转换为字符串
              char *p = buf + sizeof(buf) - 1;
              int2str(p, num);
          
              // 复制到输出缓冲区
              while (*p) {
                *out++ = *p++;
              }
              break;
            }
          case 's': {
              char *s = va_arg(ap, char *);
              while (*s) {
                *out++ = *s++;
              }
              break;
            }
          default:
            break;
        }   
        fmt++;
      default:
        *out++ = *fmt;
    }
  }
  *out = '\0';
  return out - start;
}

int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
