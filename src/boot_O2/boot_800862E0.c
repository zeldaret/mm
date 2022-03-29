#include "global.h"
#include "system_malloc.h"

typedef void (*BlockFunc)(void*);
typedef void (*BlockFunc1)(void*, u32);
typedef void (*BlockFunc8)(void*, u32, u32, u32, u32, u32, u32, u32, u32);

typedef struct InitFunc {
    uintptr_t nextOffset;
    void (*func)(void);
} InitFunc;

void* sInitFuncs = NULL;

char sNew[] = { 0x00, 0x00, 0x00, 0x00 };

char D_80097508[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00,
    0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};

void* SystemArena_MallocMin1(size_t size) {
    if (size == 0) {
        size = 1;
    }

    return __osMalloc(&gSystemArena, size);
}

void SystemArena_FreeNullCheck(void* ptr) {
    if (ptr != NULL) {
        __osFree(&gSystemArena, ptr);
    }
}

void SystemArena_RunBlockFunc(void* blk, size_t nBlk, size_t blkSize, BlockFunc blockFunc) {
    uintptr_t pos = blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        blockFunc(pos);
    }
}

void SystemArena_RunBlockFunc1(void* blk, size_t nBlk, size_t blkSize, BlockFunc1 blockFunc) {
    uintptr_t pos = blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        blockFunc(pos, 2);
    }
}

void* SystemArena_RunBlockFunc8(void* blk, size_t nBlk, size_t blkSize, BlockFunc8 blockFunc) {
    if (blk == NULL) {
        blk = SystemArena_MallocMin1(nBlk * blkSize);
    }

    if (blk != NULL && blockFunc != NULL) {
        uintptr_t pos = blk;

        for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
            blockFunc(pos, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }

    return blk;
}

void SystemArena_RunBlockFunc1Reverse(void* blk, size_t nBlk, size_t blkSize, BlockFunc1 blockFunc, s32 shouldFree) {
    uintptr_t pos;
    uintptr_t start;
    size_t maskedBlkSize;

    if (blk == NULL) {
        return;
    }

    if (blockFunc != NULL) {
        start = blk;
        maskedBlkSize = (blkSize & ~0);
        pos = (uintptr_t)start + (nBlk * blkSize);

        while (pos > start) {
            pos -= maskedBlkSize;
            blockFunc(pos, 2);
        }
    }

    if (shouldFree) {
        SystemArena_FreeNullCheck(blk);
    }
}

void SystemArena_RunInits(void) {
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

void SystemArena_Init(void* start, size_t size) {
    SystemArena_InitArena(start, size);
    SystemArena_RunInits();
}
