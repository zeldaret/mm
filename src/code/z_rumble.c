#include "global.h"
#include "z64rumble.h"

RumbleManager sRumbleMgr;

// RumbleImpl?
void func_8013EC10(UNK_TYPE arg0) {
    func_80182CE0(&sRumbleMgr);
    PadMgr_RumbleSet(sRumbleMgr.rumbleEnabled);
}

// Used by some bosses (and fishing)
void func_8013EC44(f32 distSq, u8 arg1, u8 arg2, u8 arg3) {
    s32 temp;
    s32 distance;

    if (SQ(1000.0f) < distSq) {
        distance = 1000;
    } else {
        distance = sqrtf(distSq);
    }

    if ((distance < 1000) && (arg1 != 0) && (arg3 != 0)) {
        temp = arg1 - (distance * 255) / 1000;

        if (temp > 0) {
            sRumbleMgr.unk_10A = temp;
            sRumbleMgr.unk_10B = arg2;
            sRumbleMgr.unk_10C = arg3;
        }
    }
}

// Normal rumble?
void func_8013ECE0(f32 xyzDistToPlayerSq, u8 arg1, u8 arg2, u8 arg3) {
    s32 temp;
    s32 distance;
    s32 i;

    if (SQ(1000.0f) < xyzDistToPlayerSq) {
        distance = 1000;
    } else {
        distance = sqrtf(xyzDistToPlayerSq);
    }

    if ((distance < 1000) && (arg1 != 0) && (arg3 != 0)) {
        temp = arg1 - (distance * 255) / 1000;

        for (i = 0; i < ARRAY_COUNT(sRumbleMgr.unk_04); i++) {
            if (sRumbleMgr.unk_04[i] == 0) {
                if (temp > 0) {
                    sRumbleMgr.unk_04[i] = temp;
                    sRumbleMgr.unk_44[i] = arg2;
                    sRumbleMgr.unk_84[i] = arg3;
                }
                break;
            }
        }
    }
}

void Rumble_Init(void) {
    func_80183020(&sRumbleMgr);
    func_80174F24(func_8013EC10, 0);
}

void Rumble_Destroy(void) {
    func_80174F44(func_8013EC10, 0);
    func_80183058(&sRumbleMgr);
}

s32 Rumble_ControllerOneHasRumblePak(void) {
    return PadMgr_ControllerHasRumblePak(0);
}

void func_8013EE24(void) {
    sRumbleMgr.unk_104 = 2;
}

void func_8013EE38(void) {
    sRumbleMgr.unk_104 = 0;
}

void func_8013EE48(s32 arg0) {
    sRumbleMgr.unk_105 = !!arg0;
}
