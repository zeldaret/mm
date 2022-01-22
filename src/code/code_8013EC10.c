#include "global.h"

UnkRumbleStruct D_801F69D0;

void func_8013EC10(s32 arg0) {
    func_80182CE0(&D_801F69D0);
    func_80175474(&D_801F69D0);
}

void func_8013EC44(f32 arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 temp1;
    s32 temp2;

    if (SQ(1000.0f) < arg0) {
        temp1 = 1000;
    } else {
        temp1 = sqrtf(arg0);
    }

    if ((temp1 < 1000) && (arg1 != 0) && (arg3 != 0)) {
        temp2 = arg1 - (temp1 * 255) / 1000;
        if (temp2 > 0) {
            D_801F69D0.unk_10A = temp2;
            D_801F69D0.unk_10B = arg2;
            D_801F69D0.unk_10C = arg3;
        }
    }
}

void func_8013ECE0(f32 xyzDistToPlayerSq, u8 arg1, u8 arg2, u8 arg3) {
    s32 temp_a0;
    s32 phi_v0;
    s32 i;

    if (SQ(1000.0f) < xyzDistToPlayerSq) {
        phi_v0 = 1000;
    } else {
        phi_v0 = sqrtf(xyzDistToPlayerSq);
    }

    if ((phi_v0 < 1000) && (arg1 != 0) && (arg3 != 0)) {
        temp_a0 = arg1 - ((s32) (phi_v0 * 0xFF) / 1000);

        for (i = 0; i < ARRAY_COUNT(D_801F69D0.unk_04); i++) {
            if (D_801F69D0.unk_04[i] == 0) {
                if (temp_a0 > 0) {
                    D_801F69D0.unk_04[i] = temp_a0;
                    D_801F69D0.unk_44[i] = arg2;
                    D_801F69D0.unk_84[i] = arg3;
                }
                break;
            }
        }
    }
}

void func_8013ED9C(void) {
    func_80183020(&D_801F69D0);
    func_80174F24(func_8013EC10, 0);
}

void func_8013EDD0(void) {
    func_80174F44(func_8013EC10, 0);
    func_80183058(&D_801F69D0);
}

u32 func_8013EE04(void) {
    return func_801754C0(0);
}

void func_8013EE24(void) {
    D_801F69D0.unk_104 = 2;
}

void func_8013EE38(void) {
    D_801F69D0.unk_104 = 0;
}

void func_8013EE48(s32 arg0) {
    D_801F69D0.unk_105 = arg0 != 0;
}
