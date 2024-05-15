#ifndef LIBC_ALLOCA_H
#define LIBC_ALLOCA_H

void* alloca(u32);
#define alloca  __builtin_alloca

#endif
