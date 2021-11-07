#include "global.h"

typedef struct InitFunc {
    s32 nextOffset;
    void (*func)(void);
} InitFunc;

void* sInitFuncs = NULL;

char sNew[0x4] = { 0x00, 0x00, 0x00, 0x00 };

char D_80097508[0x18] = {
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
    uintptr_t pos;

    for (pos = blk; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        arg3((void*)pos);
    }
}

void func_800863AC(void* blk, size_t nBlk, size_t blkSize, arg3_800863AC arg3) {
    uintptr_t pos;

    for (pos = blk; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        arg3((void*)pos, 2);
    }
}

void* func_8008641C(void* blk, size_t nBlk, size_t blkSize, arg3_8008641C arg3) {
    uintptr_t pos;

    if (blk == NULL) {
        blk = SystemArena_MallocMin1(nBlk * blkSize);
    }

    if (blk != NULL && arg3 != NULL) {
        pos = blk;
        while (pos < (uintptr_t)blk + (nBlk * blkSize)) {
            arg3((void*)pos, 0, 0, 0, 0, 0, 0, 0, 0);
            pos += (blkSize & ~0);
        }
    }
    return blk;
}

void func_800864EC(void* blk, size_t nBlk, size_t blkSize, arg3_800864EC arg3, s32 arg4) {
    uintptr_t pos;
    uintptr_t end;
    s32 masked_arg2;

    if (blk == NULL) {
        return;
    }

    if (arg3 != 0) {
        end = blk;
        masked_arg2 = (blkSize & ~0);
        pos = (uintptr_t)end + (nBlk * blkSize);

        while (pos > end) {
            pos -= masked_arg2;
            arg3((void*)pos, 2);
        }
    }

    if (arg4 != 0) {
        SystemArena_FreeNull(blk);
    }
}

void func_80086588(void) {
    InitFunc* initFunc = (InitFunc*)&sInitFuncs;
    u32 nextOffset = initFunc->nextOffset;
    InitFunc* prev = NULL;

    while (nextOffset != 0) {
        initFunc = (InitFunc*)((s32)initFunc + nextOffset);

        if (initFunc->func != NULL) {
            (*initFunc->func)();
        }

        nextOffset = initFunc->nextOffset;
        initFunc->nextOffset = (s32)prev;
        prev = initFunc;
    }

    sInitFuncs = prev;
}

void SystemArena_Init(void* start, size_t size) {
    SystemArena_InitArena(start, size);
    func_80086588();
}
