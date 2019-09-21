#include <ultra64.h>
#include <global.h>

#ifdef NONMATCHING

UNK_RET func_800805E0(UNK_TYPE a0) {
    if (a0 != 0) {
        switch (osTvType) {
        case 2:
            osViSetMode(&D_80098010);
            break;
        case 0:
            osViSetMode(&D_80097590);
            break;
        case 1:
            default:
            osViSetMode(&D_80097FC0);
            break;
        }

		// TODO v0 is used here instead of a0. Is this a 7.1 optimization?
        if (D_80096B2C != 0) {
            osViSetSpecialFeatures(D_80096B2C);
        }

        if (D_80096B34 != 1) {
            osViSetYScale(1);
        }
    } else {
        osViSetMode(&D_8009B240);

        if (D_80096B28 != 0) {
            func_80087E00(D_80096B28);
        }

		// TODO v0 is used here instead of a0. Is this a 7.1 optimization?
        if (D_80096B2C != 0) {
            osViSetSpecialFeatures(D_80096B2C);
        }

        if (D_80096B30 != 1) {
            osViSetXScale(D_80096B30);
        }

        if (D_80096B34 != 1) {
            osViSetYScale(D_80096B34);
        }
    }

    D_80096B24 = a0;
}


#else

GLOBAL_ASM("./asm/nonmatching/boot_0x800805E0/func_800805E0.asm")

#endif

UNK_RET func_80080748(void) {
    if (D_80096B24 != 0) {
        osViRepeatLine(1);
    } else {
        osViRepeatLine(0);
    }
}
