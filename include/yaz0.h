#ifndef YAZ0_H
#define YAZ0_H

#include "ultra64.h"

void Yaz0_Decompress(uintptr_t romStart, void* dst, size_t size);

extern void* gYaz0DecompressDstEnd;

#endif
