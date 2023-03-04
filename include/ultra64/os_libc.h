#ifndef ULTRA64_OS_LIBC_H
#define ULTRA64_OS_LIBC_H

#include "libc/stdarg.h"


void bcopy(void* __src, void* __dest, int __n);
int bcmp(void* __s1, void* __s2, int __n);
void bzero(void* begin, int length);

void* proutSprintf(void* dst, const char* fmt, size_t size);
s32 vsprintf(char* dst, char* fmt, va_list args);
int sprintf(char* dst, const char* fmt, ...);
void osSyncPrintf(const char* fmt, ...);

#endif
