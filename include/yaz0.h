#ifndef YAZ0_H
#define YAZ0_H

#include "ultra64.h"

void Yaz0_Decompress(uintptr_t romStart, void* dst, size_t size);

#if MM_VERSION >= N64_US
extern void* gYaz0DecompressDstEnd;
#endif

#endif
