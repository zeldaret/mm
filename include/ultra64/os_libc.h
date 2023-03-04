#ifndef ULTRA64_OS_LIBC_H
#define ULTRA64_OS_LIBC_H

void bcopy(void* __src, void* __dest, int __n);
int bcmp(void* __s1, void* __s2, int __n);
void bzero(void* begin, int length);

int sprintf(char* dst, const char* fmt, ...);
void osSyncPrintf(const char* fmt, ...);

#endif
