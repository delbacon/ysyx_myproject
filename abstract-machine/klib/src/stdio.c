#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <limits.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  union {
    char buf[128];
    uintptr_t align;
  } out;

  // 使用 va_list 处理变参
  va_list args;
  va_start(args, fmt);
  int len = vsprintf(out.buf, fmt, args); // 使用 vsprintf 处理格式化
  va_end(args);

  // 输出字符并统计数量
  for (int i = 0; out.buf[i] != '\0'; i++) {
    putch(out.buf[i]);
  }

  return len; // 返回实际输出字符数
}

static int int2str(char *str, int num) {
  if (str == NULL) {
    return 0;
  }
  
  int negative = 0;
  char buf[32];
  
  // 处理负数情况，特别注意INT_MIN的边界条件
  if (num < 0) {
    negative = 1;
    // 避免INT_MIN溢出，直接处理特殊情况
    if (num == INT_MIN) {
      // INT_MIN的绝对值无法用int表示，特殊处理
      const char* int_min_str = "-2147483648";
      int len = 11; // strlen("-2147483648")
      for (int i = 0; i < len; i++) {
        str[i] = int_min_str[i];
      }
      str[len] = '\0';
      return len;
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
  for (int i = 0; i <= cnt + negative; i++) {
    str[i] = buf[i];
  }
  return cnt + negative;
}

// ... existing code ...
int vsprintf(char *out, const char *fmt, va_list ap) {
  char *start = out;
  union {
    char buf[32];
    uintptr_t align;
  } aligned_buf;

  while (*fmt) {
    if (*fmt == '%') {//检测是否为格式化字符
      fmt++;
      
      // --- 新增：解析格式说明符 ---
      char flag = '\0';
      int width = 0;
      
      // 解析标志 (目前只处理 '0')
      if (*fmt == '0') {
        flag = '0';
        fmt++;
      }
      
      // 解析宽度 (一串数字)
      while (*fmt >= '0' && *fmt <= '9') {
        width = width * 10 + (*fmt - '0');
        fmt++;
        // 防止 width 过大导致后续计算溢出，设置一个合理的上限
        if (width > 31) width = 31;
      }
      // --- 解析结束 ---

      switch (*fmt) {
        case 'c': {
          char c = (char)va_arg(ap, int); 
          *out++ = c;
          break;
        }

        case 'd': {
          int num = va_arg(ap, int);
          int len = int2str(aligned_buf.buf, num);
          
          // 应用宽度和填充
          if (width > len) {
            char pad_char = (flag == '0') ? '0' : ' ';
            for (int i = 0; i < width - len; i++) {
              *out++ = pad_char;
            }
          }
          
          for (int i = 0; i < len; i++) {
            *out++ = aligned_buf.buf[i];
          }
          break;
        }

        case 'x': {
          unsigned int num = va_arg(ap, unsigned int);
          char *p = aligned_buf.buf + sizeof(aligned_buf.buf) - 1;
          *p-- = '\0';
          
          if (num == 0) {
            *p = '0';
          } else {
            while (num > 0) {
              int digit = num & 0xF;
              if (digit < 10) {
                *p = '0' + digit;
              } else {
                *p = 'a' + (digit - 10);
              }
              p--;
              num >>= 4;
            }
            p++;
          }
          
          int hex_len = strlen(p); // 计算 "0x" 后的十六进制字符串长度
          int total_len = hex_len + 2; // 加上 "0x" 的长度
          
          // 应用宽度和填充 (填充在 "0x" 之前)
          if (width > total_len) {
            char pad_char = (flag == '0') ? '0' : ' ';
            for (int i = 0; i < width - total_len; i++) {
              *out++ = pad_char;
            }
          }
          
          *out++ = '0';
          *out++ = 'x';
          while (*p) {
            *out++ = *p++;
          }
          break;
        }

        case 's': {
          char *s = va_arg(ap, char *);
          if (s == NULL) s = "(null)";
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
      *out++ = *fmt++;
    }
  }

  *out = '\0';
  return out - start;
}
// ... existing code ...


/*
int vsprintf(char *out, const char *fmt, va_list ap) {
  char *start = out;
  union {
    char buf[32];
    uintptr_t align;
  } aligned_buf;
  union {
    char buf_args[8];
    uintptr_t align;
  } aligned_buf_args;
  int args_cnt = 0;

  while (*fmt) {
    if (*fmt == '%') {//检测是否为格式化字符
      fmt++;
      while(*fmt == '0' || *fmt == '1' || *fmt == '2' || *fmt == '3' || *fmt == '4' || *fmt == '5' || *fmt == '6' || *fmt == '7' || *fmt == '8' || *fmt == '9'){
        aligned_buf_args.buf_args[args_cnt] = *fmt;
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
          char *p = aligned_buf.buf + sizeof(aligned_buf.buf) - 1;
          int len = int2str(p, num);
          if(args_cnt != 0){
            char tmp;
            if(aligned_buf_args.buf_args[0] == '0' || aligned_buf_args.buf_args[0] == '.' || aligned_buf_args.buf_args[0] == '-'){
              tmp = aligned_buf_args.buf_args[0];
              if(aligned_buf_args.buf_args[1] == '1' || aligned_buf_args.buf_args[1] == '2' || aligned_buf_args.buf_args[1] == '3' || aligned_buf_args.buf_args[1] == '4' || aligned_buf_args.buf_args[1] == '5' || aligned_buf_args.buf_args[1] == '6' || aligned_buf_args.buf_args[1] == '7' || aligned_buf_args.buf_args[1] == '8' || aligned_buf_args.buf_args[1] == '9'){
                int tmp_num = aligned_buf_args.buf_args[1] - 48;
                for(int i = 0; i < tmp_num && i < (tmp_num - len ); i++){
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
          char *p = aligned_buf.buf + sizeof(aligned_buf.buf) - 1;
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
*/
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
