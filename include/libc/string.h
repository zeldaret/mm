#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include "libc/stddef.h"

const char* strchr(const char* s, int c);
size_t strlen(const char* s);
void* memcpy(void* s1, const void* s2, size_t n);

void* memset(void* ptr, int val, size_t size);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* dst, const char* src);
void* memmove(void* dst, const void* src, size_t size);

#endif
