#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

//获取字符串长度，识别到 /0 时停止 
//test
size_t strlen(const char *s) {
  if(s == NULL) return 0;
  size_t len = 0;
  while(*s != '\0') {
    len++;
    s++;
  }
  return len;
}
//复制字符串
//test
char *strcpy(char *dst, const char *src) {
  if (dst == NULL || src == NULL) return NULL; 

  char *ret = dst;
  while(*src != '\0'){
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
  return ret;
}

//库函数里实现的不会在末尾自动添加\0
//test
char *strncpy(char *dst, const char *src, size_t n) {

  char *ret = dst;
  size_t len = 0;
  while (len < n && *src != '\0') {
    *dst = *src;
    src++;
    dst++;
    len++;
  }
  // 用 \0 填充剩余空间
  while(len < n){
    *dst = '\0';
    dst++;
    len++;
  }

  return ret;
}

//拼接字符串
//test
char *strcat(char *dst, const char *src) {
  if(dst == NULL || src == NULL) return NULL;

  char *ret = dst;
  while(*dst != '\0') dst++;

  while(*src != '\0'){
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
  return ret;
}

//比较字符串
//test
int strcmp(const char *s1, const char *s2) {
  if (s1 == NULL || s2 == NULL) {
    return (s1 == NULL) - (s2 == NULL); 
  }

    while( (*s1 != '\0') && (*s1 == *s2) ){ 
      s1++;
      s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

//比较给定长度的字符串
//test
int strncmp(const char *s1, const char *s2, size_t n) {
  if(n == 0) return 0;
  if (s1 == NULL || s2 == NULL) {
    return (s1 == NULL) - (s2 == NULL); 
  }

    while( (*s1 != '\0') && (*s1 == *s2) && n>0){ 
      s1++;
      s2++;
      n--; 
    }
    if(n==0) return 0;
    return (unsigned char )*s1 - (unsigned char )*s2;
}

// 写内存
//test
void *memset(void *s, int c, size_t n) {
  if(s == NULL) return NULL;
  
  unsigned char *p = s;
  unsigned char ch = (unsigned char)c;
  
  while(n>0){
    *p++ = ch;
    n--;
  }
  return s;
}

// 拷贝内存内容（允许重叠）
// test
void *memmove(void *dst, const void *src, size_t n) {
  if(dst == NULL || src == NULL) return NULL;

  unsigned char *p_dst = dst;
  const unsigned char *p_src = src;
    if (p_dst < p_src){
        while (n>0){
            *p_dst++ = *p_src++;
            n--;
        }
    }
    /* 如果目标地址在源地址之后，反向拷贝 */
    else if (p_dst > p_src){
        p_dst += n;
        p_src += n;
        while (n>0){
            *(--p_dst) = *(--p_src);
            n--;
        }
    }

    return dst;
}

// 复制内存内容（不允许重叠)
// test
void *memcpy(void *out, const void *in, size_t n) {
  if(out == NULL || in == NULL) return NULL;

  unsigned char *p_dst = out;
  const unsigned char *p_src = in;
  while (n>0){
    *p_dst++ = *p_src++;
     n--;
  }
  return out;
}

// 比较内存内容
// test
int memcmp(const void *s1, const void *s2, size_t n) {
  if (s1 == NULL || s2 == NULL) {
    return (s1 == NULL) - (s2 == NULL); 
  }

  const unsigned char *p_s1 = s1;
  const unsigned char *p_s2 = s2;
    while( (*p_s1 != '\0') && (*p_s1 == *p_s2) && n>0){ 
      p_s1++;
      p_s2++;
      n--; 
    }
    if(n==0) return 0;
    return (unsigned char )*p_s1 - (unsigned char )*p_s2;
}

#endif
