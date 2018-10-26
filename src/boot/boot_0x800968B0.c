#include <ultra64.h>
#include <global.h>

u32 func_800968B0(const u8* a0, const u8* a1) {
    u8 v0;
    u8 v1;
    do {
        v0 = *a0++;
        v1 = *a1++;
        if (v0 != v1) {
            return v0 - v1;
        }
    } while (v0 != 0);
    return 0;
}
