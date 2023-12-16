#ifndef YAZ0_H
#define YAZ0_H

#include "ultra64.h"

#define YAZ0_MAGIC 0x59617A30 // 'Yaz0'

typedef struct {
    /* 0x0 */ u32 magic;
    /* 0x4 */ u32 decSize;
    /* 0x8 */ u32 compInfoOffset;   // only used in mio0
    /* 0xC */ u32 uncompDataOffset; // only used in mio0
} Yaz0Header; // size = 0x10

void Yaz0_Decompress(uintptr_t romStart, void* dst, size_t size);

extern void* gYaz0DecompressDstEnd;

#endif
