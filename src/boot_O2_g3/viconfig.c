#include <ultra64.h>
#include <global.h>

void ViConfig_UpdateVi(u32 mode) {
    if (mode != 0) {
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

        if (gViConfigFeatures != 0) {
            osViSetSpecialFeatures(gViConfigFeatures);
        }

        if (gViConfigYScale != 1) {
            osViSetYScale(1);
        }
    } else {
        osViSetMode(&gViConfigMode);

        if (gViConfigAdditionalScanLines != 0) {
            func_80087E00(gViConfigAdditionalScanLines);
        }

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

    gViConfigUseDefault = mode;
}

void ViConfig_UpdateBlack(void) {
    if (gViConfigUseDefault != 0) {
        osViBlack(1);
    } else {
        osViBlack(0);
    }
}
