#include <ultra64.h>
#include <global.h>

s800E03A0* func_800E03A0(s32 a0) {
    if ((a0 < 0) || (a0 > 22)) return 0;
    return &((&D_801B9F20)[a0]);
}

// Probably zeroes out a s800E03A0?
void func_800E03CC(u8* a0) {
    s32 i;
    u8* v1;
    
    for (i = 0, v1 = a0; i < 32; i++) {
        *v1++ = 0;
    }
}
