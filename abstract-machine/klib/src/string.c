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
char *strncpy(char *dst, const char *src, size_t n) {
  if(dst == NULL || src == NULL) return NULL;

  char *ret = dst;
  while (n > 0) {
    if (*src != '\0') {
      *dst = *src;
      src++;
    } else {
      *dst = '\0'; 
    }
    dst++;
    n--;
  }
  

  return ret;
}

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

void *memset(void *s, int c, size_t n) {
  if(s == NULL) return NULL;
  
  unsigned char *p = s;
  while(n>0){
    *p++ = (unsigned char)c;
    n--;
  }
  return s;
}

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
