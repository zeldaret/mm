#include "global.h"

void EnvFlags_UnsetAll(GlobalContext* globalCtx) {
    u8 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->envFlags); i++) {
        globalCtx->envFlags[i] = 0;
    }
}

void EnvFlags_Set(GlobalContext* globalCtx, s16 flag) {
    s16 index = flag / 16;
    s16 bit = flag % 16;
    s16 mask = 1 << bit;

    globalCtx->envFlags[index] |= mask;
}

void EnvFlags_Unset(GlobalContext* globalCtx, s16 flag) {
    s16 index = flag / 16;
    s16 bit = flag % 16;
    s16 mask = (1 << bit) ^ 0xFFFF;

    globalCtx->envFlags[index] &= mask;
}

s32 EnvFlags_Get(GlobalContext* globalCtx, s16 flag) {
    s16 index = flag / 16;
    s16 bit = flag % 16;
    s16 mask = 1 << bit;

    return globalCtx->envFlags[index] & mask;
}
