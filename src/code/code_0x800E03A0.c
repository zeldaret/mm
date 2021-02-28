#include <ultra64.h>
#include <global.h>

ActorDamageChart* func_800E03A0(s32 index) {
    if (index < 0 || index > 22) {
        return 0;
    }

    return &(D_801B9F20[index]);
}

// Probably zeroes out a damage chart?
void func_800E03CC(u8* a0) {
    s32 i;
    u8* v1;

    for (i = 0, v1 = a0; i < 32; i++) {
        *v1++ = 0;
    }
}
