#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  if(s == NULL) return 0;
  size_t len = 0;
  while(*s != '\0') {
    len++;
    s++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  while(*src != '\0'){
    *dst = *src;
    src++;
    dst++;
  }
  *dst = '\0';
  return dst;
}

//库函数里实现的不会自动添加\0
char *strncpy(char *dst, const char *src, size_t n) {
  if(n == 0) return dst;

  while(n--){
    //如果n>src的长度，则dst剩余部分由\0填充
    if(*src == '\0'){
      while(n--){
        *dst = '\0';
        dst++;
      }
//      *dst = '\0';
      return dst;
    }

    *dst = *src;
    src++;
    dst++;
  }
//  *dst = '\0';

  return dst;
}

char *strcat(char *dst, const char *src) {
  while(*dst != '\0') dst++;
  while(*src != '\0'){
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  panic("Not implemented");
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  panic("Not implemented");
}

#endif
