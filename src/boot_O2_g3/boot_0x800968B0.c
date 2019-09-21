#include <ultra64.h>
#include <global.h>

#ifdef NONMATCHING

u32 func_800968B0(const u8* a0, const u8* a1) {
    u8 v0;
    u8 v1;
    do {
        v0 = *a0++;
        v1 = *a1++;
        if (v0 != v1) {
			// TODO this uses v0 instead of a3
            return v0 - v1;
        }
    } while (v0 != 0);
    return 0;
}

#else

GLOBAL_ASM("./asm/nonmatching/boot_0x800968B0/func_800968B0.asm")

#endif