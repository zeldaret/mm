#include "global.h"
#include "z64rumble.h"

RumbleManager gRumbleMgr;

void Rumble_Update(void* arg0) {
    RumbleManager_Update(&gRumbleMgr);
    PadMgr_RumbleSet(gRumbleMgr.rumbleEnabled);
}

// Used by some bosses (and fishing)
void Rumble_Override(f32 distSq, u8 arg1, u8 arg2, u8 decreaseStep) {
    s32 temp;
    s32 distance;

    if (SQ(1000.0f) < distSq) {
        distance = 1000;
    } else {
        distance = sqrtf(distSq);
    }

    if ((distance < 1000) && (arg1 != 0) && (decreaseStep != 0)) {
        temp = arg1 - (distance * 255) / 1000;

        if (temp > 0) {
            gRumbleMgr.unk_10A = temp;
            gRumbleMgr.unk_10B = arg2;
            gRumbleMgr.decreaseStepForced = decreaseStep;
        }
    }
}

void Rumble_Request(f32 distSq, u8 arg1, u8 arg2, u8 decreaseStep) {
    s32 temp;
    s32 distance;
    s32 i;

    if (SQ(1000.0f) < distSq) {
        distance = 1000;
    } else {
        distance = sqrtf(distSq);
    }

    if ((distance < 1000) && (arg1 != 0) && (decreaseStep != 0)) {
        temp = arg1 - (distance * 255) / 1000;

        for (i = 0; i < RUMBLE_REQUEST_BUFFER_SIZE; i++) {
            if (gRumbleMgr.unk_04[i] == 0) {
                if (temp > 0) {
                    gRumbleMgr.unk_04[i] = temp;
                    gRumbleMgr.unk_44[i] = arg2;
                    gRumbleMgr.decreaseStep[i] = decreaseStep;
                }
                break;
            }
        }
    }
}

void Rumble_Init(void) {
    RumbleManager_Init(&gRumbleMgr);
    func_80174F24(Rumble_Update, NULL);
}

void Rumble_Destroy(void) {
    func_80174F44(Rumble_Update, NULL);
    RumbleManager_Destroy(&gRumbleMgr);
}

s32 Rumble_ControllerOneHasRumblePak(void) {
    return PadMgr_ControllerHasRumblePak(0);
}

void func_8013EE24(void) {
    gRumbleMgr.state = RUMBLEMANAGER_STATE_INITIAL;
}

void func_8013EE38(void) {
    gRumbleMgr.state = RUMBLEMANAGER_STATE_0;
}

// Rumble_SetEnableUpdate? unk_105 seems to control if RumbleManager should update or not
void func_8013EE48(s32 arg0) {
    gRumbleMgr.unk_105 = !!arg0;
}
