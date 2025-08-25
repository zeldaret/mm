#ifndef LIBC64_OS_MALLOC_H
#define LIBC64_OS_MALLOC_H

#include "ultra64.h"
#include "stddef.h"

#include "unk.h"
#include "versions.h"

typedef struct ArenaNode {
    /* 0x0 */ s16 magic; // Should always be 0x7373
    /* 0x2 */ s16 isFree;
    /* 0x4 */ size_t size;
    /* 0x8 */ struct ArenaNode* next;
    /* 0xC */ struct ArenaNode* prev;
    #if MM_VERSION <= N64_JP_1_1
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ OSId unk_18;
    /* 0x1C */ void *unk_1C;
    /* 0x20 */ OSTime unk_20;
    /* 0x28 */ UNK_TYPE1 unk_28[0x8];
    #endif
} ArenaNode; // size = 0x10

typedef struct Arena {
    /* 0x00 */ ArenaNode* head;
    /* 0x04 */ void* start;
    /* 0x08 */ OSMesgQueue lock;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 isInit;
    /* 0x22 */ u8 flag;
} Arena; // size = 0x24

void __osMallocInit(Arena* arena, void* heap, size_t size);
void __osMallocCleanup(Arena* arena);
u8 __osMallocIsInitialized(Arena* arena);
void* __osMalloc(Arena* arena, size_t size);
void* __osMallocR(Arena* arena, size_t size);
void __osFree(Arena* arena, void* ptr);
void* __osRealloc(Arena* arena, void* ptr, size_t newSize);
void __osGetSizes(Arena* arena, size_t* outMaxFree, size_t* outFree, size_t* outAlloc);
s32 __osCheckArena(Arena* arena);

#if MM_VERSION <= N64_JP_1_1
void *__osMallocDebug(Arena *arena, size_t size, s32 arg2, s32 arg3);
void *__osMallocRDebug(Arena *arena, size_t size, s32 arg2, s32 arg3);

void *__osReallocDebug(Arena* arena, void* ptr, size_t newSize, const char* file, int line);
#endif

#endif
