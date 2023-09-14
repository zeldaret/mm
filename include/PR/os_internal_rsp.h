#ifndef PR_OS_INTERNAL_RSP_H
#define PR_OS_INTERNAL_RSP_H

#include "ultratypes.h"
#include "libc/stddef.h"

u32 __osSpGetStatus(void);
void __osSpSetStatus(u32 data);
s32 __osSpSetPc(void* pc);
s32 __osSpRawStartDma(s32 direction, void* devAddr, void* dramAddr, size_t size);


#endif
