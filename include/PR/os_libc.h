#ifndef PR_OS_LIBC_H
#define PR_OS_LIBC_H

#include "libc/stdarg.h"


void bcopy(void* __src, void* __dest, int __n);
int bcmp(void* __s1, void* __s2, int __n);
void bzero(void* begin, int length);

void osSyncPrintf(const char* fmt, ...);

#endif
