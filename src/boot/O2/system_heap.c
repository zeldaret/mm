/**
 * @file system_heap.c
 *
 * @note:
 *  Only SystemHeap_Init() is used, and is essentially just a wrapper for MallocInit().
 *
 */
#include "global.h"
#include "libc64/malloc.h"

typedef void (*BlockFunc)(uintptr_t);
typedef void (*BlockFunc1)(uintptr_t, u32);
typedef void (*BlockFunc8)(uintptr_t, u32, u32, u32, u32, u32, u32, u32, u32);

typedef struct InitFunc {
    /* 0x0 */ uintptr_t nextOffset;
    /* 0x4 */ void (*func)(void);
} InitFunc; // size = 0x8

void* sInitFuncs = NULL;

char sNew[] = "";

UNK_TYPE1 D_80097508[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00,
    0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};

void* SystemHeap_Malloc(size_t size) {
    if (size == 0) {
        size = 1;
    }

    return __osMalloc(&malloc_arena, size);
}

void SystemHeap_Free(void* ptr) {
    if (ptr != NULL) {
        __osFree(&malloc_arena, ptr);
    }
}

void SystemHeap_RunBlockFunc(void* blk, size_t nBlk, size_t blkSize, BlockFunc blockFunc) {
    uintptr_t pos = (uintptr_t)blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        blockFunc(pos);
    }
}

void SystemHeap_RunBlockFunc1(void* blk, size_t nBlk, size_t blkSize, BlockFunc1 blockFunc) {
    uintptr_t pos = (uintptr_t)blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        blockFunc(pos, 2);
    }
}

void* SystemHeap_RunBlockFunc8(void* blk, size_t nBlk, size_t blkSize, BlockFunc8 blockFunc) {
    if (blk == NULL) {
        blk = SystemHeap_Malloc(nBlk * blkSize);
    }

    if ((blk != NULL) && (blockFunc != NULL)) {
        uintptr_t pos = (uintptr_t)blk;

        for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
            blockFunc(pos, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }

    return blk;
}

void SystemHeap_RunBlockFunc1Reverse(void* blk, size_t nBlk, size_t blkSize, BlockFunc1 blockFunc, s32 shouldFree) {
    uintptr_t pos;
    uintptr_t start;
    size_t maskedBlkSize;

    if (blk == NULL) {
        return;
    }

    if (blockFunc != NULL) {
        start = (uintptr_t)blk;
        maskedBlkSize = (blkSize & ~0);
        pos = (uintptr_t)start + (nBlk * blkSize);

        while (pos > start) {
            pos -= maskedBlkSize;
            blockFunc(pos, 2);
        }
    }

    if (shouldFree) {
        SystemHeap_Free(blk);
    }
}

void SystemHeap_RunInits(void) {
    InitFunc* initFunc = (InitFunc*)&sInitFuncs;
    u32 nextOffset = initFunc->nextOffset;
    InitFunc* prev = NULL;

    while (nextOffset != 0) {
        initFunc = (InitFunc*)((uintptr_t)initFunc + nextOffset);

        if (initFunc->func != NULL) {
            (*initFunc->func)();
        }

        nextOffset = initFunc->nextOffset;
        initFunc->nextOffset = (uintptr_t)prev;
        prev = initFunc;
    }

    sInitFuncs = prev;
}

void SystemHeap_Init(void* start, size_t size) {
    MallocInit(start, size);
    SystemHeap_RunInits();
}
