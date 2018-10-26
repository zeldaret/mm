#include <ultra64.h>
#include <global.h>

UNK_RET func_800805E0(UNK_TYPE a0) {
    if (a0 != 0) {
        switch (osTvType) {
        case 2:
            func_8008B650(&D_80098010);
            break;
        case 0:
            func_8008B650(&D_80097590);
            break;
        case 1:
            default:
            func_8008B650(&D_80097FC0);
            break;
        }
        
        if (D_80096B2C != 0) {
            func_80092100(D_80096B2C);
        }
        
        if (D_80096B34 != 1) {
            func_80095900(1);
        }
    } else {
        func_8008B650(&D_8009B240);
        
        if (D_80096B28 != 0) {
            func_80087E00(D_80096B28);
        }
        
        if (D_80096B2C != 0) {
            func_80092100(D_80096B2C);
        }
        
        if (D_80096B30 != 1) {
            func_80095950(D_80096B30);
        }
        
        if (D_80096B34 != 1) {
            func_80095900(D_80096B34);
        }
    }
    
    *D_80096B24 = a0;
}

UNK_RET func_80080748(void) {
    if (*D_80096B24 != 0) {
        func_8008AE70(1);
    } else {
        func_8008AE70(0);
    }
}
