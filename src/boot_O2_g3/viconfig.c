#include <ultra64.h>
#include <global.h>

#ifdef NON_MATCHING
void ViConfig_UpdateVi(u32 arg0) {
    if (arg0 != 0) {
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
        if (gViConfigFeatures != 0) {
            osViSetSpecialFeatures(gViConfigFeatures);
        }

        if (gViConfigYScale != 1) {
            osViSetYScale(1);
        }
    } else {
        osViSetMode(&D_8009B240);

        if (gViConfigAdditionalScanLines != 0) {
            func_80087E00(gViConfigAdditionalScanLines);
        }

		// TODO v0 is used here instead of a0. Is this a 7.1 optimization?
        if (gViConfigFeatures != 0) {
            osViSetSpecialFeatures(gViConfigFeatures);
        }

        if (gViConfigXScale != 1) {
            osViSetXScale(gViConfigXScale);
        }

        if (gViConfigYScale != 1) {
            osViSetYScale(gViConfigYScale);
        }
    }

    gViConfigUseDefault = arg0;
}
#else
GLOBAL_ASM("./asm/non_matchings/viconfig/ViConfig_UpdateVi.asm")
#endif

void ViConfig_UpdateBlack(void) {
    if (gViConfigUseDefault != 0) {
        osViBlack(1);
    } else {
        osViBlack(0);
    }
}
