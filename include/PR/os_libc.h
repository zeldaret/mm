#ifndef PR_OS_LIBC_H
#define PR_OS_LIBC_H

#include "stdarg.h"

#ifdef __GNUC__
void bzero(void* begin, unsigned int length);
int bcmp(const void* __s1, const void* __s2, unsigned int __n);
void bcopy(const void* __src, void* __dest, unsigned int __n);
#else
void bzero(void* begin, int length);
int bcmp(const void* __s1, const void* __s2, int __n);
void bcopy(const void* __src, void* __dest, int __n);
#endif

void osSyncPrintf(const char* fmt, ...);

#endif
