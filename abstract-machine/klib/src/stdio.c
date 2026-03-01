#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  char out[128];

  // 使用 va_list 处理变参
  va_list args;
  va_start(args, fmt);
  int len = vsprintf(out, fmt, args); // 使用 vsprintf 处理格式化
  va_end(args);

  // 输出字符并统计数量
  for (int i = 0; out[i] != '\0'; i++) {
    putch(out[i]);
  }

  return len; // 返回实际输出字符数
}

static int int2str(char *str, int num) {
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
      return 0;
    }
    num = -num;
  }

  int cnt = 0;
  int temp_num = num; 
  
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
  return cnt;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *start = out;
  char buf[32];
  char buf_args[8];
  int args_cnt=0;

  while (*fmt) {
    if (*fmt == '%') {//检测是否为格式化字符
      fmt++;
      while(*fmt == '0' || *fmt == '1' || *fmt == '2' || *fmt == '3' || *fmt == '4' || *fmt == '5' || *fmt == '6' || *fmt == '7' || *fmt == '8' || *fmt == '9'){
        buf_args[args_cnt] = *fmt;
        args_cnt++;
        fmt++;
      }
      switch (*fmt) {
        case 'c': {
          char c = (char)va_arg(ap, int); 
          *out++ = c;
          break;
        }

        case 'd': {
          int num = va_arg(ap, int);
          char *p = buf + sizeof(buf) - 1;
          int len = int2str(p, num);
          if(args_cnt != 0){
            char tmp;
            if(buf_args[0] == '0' || buf_args[0] == '.' || buf_args[0] == '-'){
              tmp = buf_args[0];
              if(buf_args[1] == '1' || buf_args[1] == '2' || buf_args[1] == '3' || buf_args[1] == '4' || buf_args[1] == '5' || buf_args[1] == '6' || buf_args[1] == '7' || buf_args[1] == '8' || buf_args[1] == '9'){
                int tmp_num = buf_args[1] - 48;
                for(int i = 0; i < tmp_num && i < (tmp_num - len); i++){
                  *out++ = tmp;
                }
              }
            }
            args_cnt = 0;
          }
          while (*p) {
            *out++ = *p++;
          }
          break;
        }

        case 'x': {
          int num = va_arg(ap, int);
          char *p = buf + sizeof(buf) - 1;
          int2str(p, num);
          *out++ = '0';
          *out++ = 'x';
          while (*p) {
            *out++ = *p++;
          } 
        }

        case 's': {
          char *s = va_arg(ap, char *);
          if (s == NULL) s = "(null)"; // 安全处理空指针
          while (*s) {
            *out++ = *s++;
          }
          break;
        }
        
        default:
          // 忽略无效格式符
          break;
      }
      fmt++;
    } else {
      *out++ = *fmt++; // 直接复制普通字符
    }
  }

  *out = '\0'; // 添加字符串结束符
  return out - start; // 返回写入字符数
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  return vsprintf(out, fmt, ap);
  va_end(ap);
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
