#ifndef LIBC_ALLOCA_H
#define LIBC_ALLOCA_H

void* alloca(size_t);
#define alloca(size) __builtin_alloca(size)

#endif
