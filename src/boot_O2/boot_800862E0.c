#include "global.h"
#include "system_malloc.h"

typedef void (*arg3_8008633C)(void*);
typedef void (*arg3_800863AC)(void*, u32);
typedef void (*arg3_8008641C)(void*, u32, u32, u32, u32, u32, u32, u32, u32);

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

void SystemArena_FreeNull(void* ptr) {
    if (ptr != NULL) {
        __osFree(&gSystemArena, ptr);
    }
}

void func_8008633C(void* blk, size_t nBlk, size_t blkSize, arg3_8008633C arg3) {
    uintptr_t pos = blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        arg3(pos);
    }
}

void func_800863AC(void* blk, size_t nBlk, size_t blkSize, arg3_800863AC arg3) {
    uintptr_t pos = blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        arg3(pos, 2);
    }
}

void* func_8008641C(void* blk, size_t nBlk, size_t blkSize, arg3_8008641C arg3) {
    if (blk == NULL) {
        blk = SystemArena_MallocMin1(nBlk * blkSize);
    }

    if (blk != NULL && arg3 != NULL) {
        uintptr_t pos = blk;

        for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
            arg3(pos, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }

    return blk;
}

void func_800864EC(void* blk, size_t nBlk, size_t blkSize, arg3_800863AC arg3, s32 shouldFree) {
    uintptr_t pos;
    uintptr_t start;
    size_t step;

    if (blk == NULL) {
        return;
    }

    if (arg3 != NULL) {
        start = blk;
        step = (blkSize & ~0);
        pos = (uintptr_t)start + (nBlk * blkSize);

        while (pos > start) {
            pos -= step;
            arg3(pos, 2);
        }
    }

    if (shouldFree) {
        SystemArena_FreeNull(blk);
    }
}

void func_80086588(void) {
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
    func_80086588();
}
