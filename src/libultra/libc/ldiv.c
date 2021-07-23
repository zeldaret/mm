#include "ultra64.h"
#include "global.h"

#ifdef NON_MATCHING
ldiv_t ldiv(long numer, long denom) {
    ldiv_t val;

    val.quot = numer / denom;
    val.rem = numer - denom * val.quot;
    if (val.quot < 0 && val.rem > 0) {
        val.quot++;
        val.rem -= denom;
    }

    return val;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/ldiv/ldiv.s")
#endif

#ifdef NON_MATCHING
lldiv_t lldiv(long long numer, long long denom) {
    lldiv_t val;

    val.quot = numer / denom;
    val.rem = numer - denom * val.quot;
    if (val.quot < 0 && val.rem > 0) {
        val.quot++;
        val.rem -= denom;
    }

    return val;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/ldiv/lldiv.s")
#endif
