#include <ultra64.h>
#include <global.h>

#ifdef NON_MATCHING
UNK_RET func_800805E0(UNK_TYPE a0) {
    if (a0 != 0) {
        switch (osTvType) {
        case 2:
            osViSetMode(&osViModeMpalLan1);
            break;
        case 0:
            osViSetMode(&osViModePalLan1);
            break;
        case 1:
            default:
            osViSetMode(&osViModeNtscLan1);
            break;
        }

		// TODO v0 is used here instead of a0. Is this a 7.1 optimization?
        if (viEnabledSpecialFeatures != 0) {
            osViSetSpecialFeatures(viEnabledSpecialFeatures);
        }

        if (screenYScale != 1) {
            osViSetYScale(1);
        }
    } else {
        osViSetMode(&D_8009B240);

        if (D_80096B28 != 0) {
            func_80087E00(D_80096B28);
        }

		// TODO v0 is used here instead of a0. Is this a 7.1 optimization?
        if (viEnabledSpecialFeatures != 0) {
            osViSetSpecialFeatures(viEnabledSpecialFeatures);
        }

        if (screenXScale != 1) {
            osViSetXScale(screenXScale);
        }

        if (screenYScale != 1) {
            osViSetYScale(screenYScale);
        }
    }

    D_80096B24 = a0;
}
#else
GLOBAL_ASM("./asm/non_matchings/boot_0x800805E0/func_800805E0.asm")
#endif

UNK_RET func_80080748(void) {
    if (D_80096B24 != 0) {
        osViRepeatLine(1);
    } else {
        osViRepeatLine(0);
    }
}
