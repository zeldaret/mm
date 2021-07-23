#include <ultra64.h>
#include <global.h>

#ifdef NON_MATCHING
short coss(unsigned short x) {
    return sins(x + 0x4000);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/coss/coss.s")
#endif
