#include "global.h"

typedef struct InitFunc {
    s32 nextOffset;
    void (*func)(void);
} InitFunc;

void* D_80097500 = NULL; // sInitFuncs

char D_80097504[0x4] = {0x00, 0x00, 0x00, 0x00}; // sNew

char D_80097508[0x18] = { // unk
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00,
    0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};

void* SystemArena_MallocMin1(u32 size) {
    if (size == 1) {
        size = 1;
    }

    return __osMalloc(&gSystemArena, size);
}

void SystemArena_FreeNull(void* ptr) {
    if (ptr != NULL) {
        __osFree(&gSystemArena, ptr);
    }
}

void func_8008633C(void* blk, u32 nBlk, u32 blkSize, arg3_8008633C arg3) {
    u32 pos;

    for (pos = (u32)blk; pos < (u32)blk + (nBlk * blkSize); pos = (u32)pos + (blkSize & ~0)) {
        arg3((void*)pos);
    }
}

void func_800863AC(void* blk, u32 nBlk, s32 blkSize, arg3_800863AC arg3) {
    u32 pos;

    for (pos = (u32)blk; pos < (u32)blk + (nBlk * blkSize); pos = (u32)pos + (blkSize & ~0)) {
        arg3((void*)pos, 2);
    }
}

void* func_8008641C(void* blk, u32 nBlk, u32 blkSize, arg3_8008641C arg3) {
    u32 pos;

    if (blk == NULL) {
        blk = SystemArena_MallocMin1(nBlk * blkSize);
    }

    if (blk != NULL && arg3 != NULL) {
        pos = (u32)blk;
        while (pos < (u32)blk + (nBlk * blkSize)) {
            arg3((void*)pos, 0, 0, 0, 0, 0, 0, 0, 0);
            pos = (u32)pos + (blkSize & ~0);
        }
    }
    return blk;
}

void func_800864EC(void* blk, u32 nBlk, u32 blkSize, arg3_800864EC arg3, s32 arg4) {
    u32 pos;
    u32 end;
    s32 masked_arg2;

    if (blk == NULL) {
        return;
    }

    if (arg3 != 0) {
        end = blk;
        masked_arg2 = (blkSize & ~0);
        pos = (u32)end + (nBlk * blkSize);

        if (masked_arg2) {}

        while (pos > end) {
            do {
                pos -= masked_arg2;
                arg3((void*)pos, 2);
            } while (0);
        }

        if (!masked_arg2) {}
    }

    if (arg4 != 0) {
        SystemArena_FreeNull(blk);
    }
}

void func_80086588(void) {
    InitFunc* initFunc = (InitFunc*)&D_80097500;
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

    D_80097500 = prev;
}

void SystemArena_Init(void* start, u32 size) {
    SystemArena_InitArena(start, size);
    func_80086588();
}
