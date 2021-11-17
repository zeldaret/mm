#include "global.h"

void ViConfig_UpdateVi(u32 mode) {
    if (mode != 0) {
        switch (osTvType) {
            case OS_TV_MPAL:
                osViSetMode(&osViModeMpalLan1);
                break;
            case OS_TV_PAL:
                osViSetMode(&osViModePalLan1);
                break;
            case OS_TV_NTSC:
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
            osViExtendVStart(gViConfigAdditionalScanLines);
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
        osViBlack(true);
    } else {
        osViBlack(false);
    }
}
