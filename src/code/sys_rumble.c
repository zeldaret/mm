#include "global.h"
#include "z64rumble.h"

// sRumbleWasEnabledonLastFrame? Probably name it after unk_105
u8 D_801D1E70 = true;

void RumbleManager_Update(RumbleManager* rumbleMgr) {
    s32 index = -1;
    s32 i;
    s32 temp;

    // Turn of rumbling for all controllers
    for (i = 0; i < ARRAY_COUNT(rumbleMgr->rumbleEnabled); i++) {
        rumbleMgr->rumbleEnabled[i] = false;
    }

    // Rumbling update is disabled (?)
    if (!rumbleMgr->unk_105) {
        if (D_801D1E70) {
            for (i = 0; i < MAXCONTROLLERS; i++) {
                func_8017544C(i, false);
            }
        }

        D_801D1E70 = rumbleMgr->unk_105;

        func_80175434();

        return;
    }

    D_801D1E70 = rumbleMgr->unk_105;

    if (rumbleMgr->state == RUMBLEMANAGER_STATE_INITIAL) {
        for (i = 0; i < MAXCONTROLLERS; ++i) {
            func_8017544C(i, false);
        }

        for (i = 0; i < ARRAY_COUNT(rumbleMgr->unk_04); i++) {
            rumbleMgr->unk_04[i] = 0;
            rumbleMgr->unk_44[i] = 0;
            rumbleMgr->decreaseStep[i] = 0;
            rumbleMgr->unk_C4[i] = 0;
        }

        rumbleMgr->rumblingTimer = 0;
        rumbleMgr->unk_108 = 0;

        rumbleMgr->unk_10A = 0;
        rumbleMgr->unk_10B = 0;
        rumbleMgr->decreaseStepForced = 0;
        rumbleMgr->unk_10D = 0;

        rumbleMgr->state = RUMBLEMANAGER_STATE_1;

        func_80175434();
    }

    if (rumbleMgr->state != RUMBLEMANAGER_STATE_0) {
        // Process arrays of rumble requests
        for (i = 0; i < ARRAY_COUNT(rumbleMgr->unk_04); i++) {
            if (rumbleMgr->unk_04[i] != 0) { // This entry has a non-empty rumble request
                if (rumbleMgr->unk_44[i] > 0) {
                    rumbleMgr->unk_44[i]--;
                } else {
                    temp = rumbleMgr->unk_04[i] - rumbleMgr->decreaseStep[i];
                    if (temp > 0) {
                        rumbleMgr->unk_04[i] = temp;
                    } else {
                        rumbleMgr->unk_04[i] = 0;
                    }
                }

                temp = rumbleMgr->unk_C4[i] + rumbleMgr->unk_04[i];
                rumbleMgr->unk_C4[i] = temp; // overflows
                if (index == -1) {
                    index = i;
                    rumbleMgr->rumbleEnabled[0] = (temp >= 0x100);
                } else if (rumbleMgr->unk_04[index] < rumbleMgr->unk_04[i]) {
                    index = i;
                    rumbleMgr->rumbleEnabled[0] = (temp >= 0x100);
                }
            }
        }

        // Process Forced request. Note it takes priority over the values set by the request arrays
        if (rumbleMgr->unk_10A != 0) {
            if (rumbleMgr->unk_10B > 0) {
                rumbleMgr->unk_10B--;
            } else {
                temp = rumbleMgr->unk_10A - rumbleMgr->decreaseStepForced;
                if (temp > 0) {
                    rumbleMgr->unk_10A = temp;
                } else {
                    rumbleMgr->unk_10A = 0;
                }
            }

            temp = rumbleMgr->unk_10D + rumbleMgr->unk_10A;
            rumbleMgr->unk_10D = temp; // overflows
            rumbleMgr->rumbleEnabled[0] = (temp >= 0x100);
        }

        if (rumbleMgr->unk_10A != 0) {
            temp = rumbleMgr->unk_10A;
        } else if (index == -1) {
            temp = 0;
        } else {
            temp = rumbleMgr->unk_04[index];
        }

        if (temp == 0) {
            rumbleMgr->unk_108++;
            if (rumbleMgr->unk_108 > 5) {
                rumbleMgr->rumblingTimer = 0;
                rumbleMgr->unk_108 = 5;
            }
        } else {
            rumbleMgr->unk_108 = 0;
            rumbleMgr->rumblingTimer++;
            if (rumbleMgr->rumblingTimer > 2 * 60 * 60) { // 2 minutes
                rumbleMgr->state = RUMBLEMANAGER_STATE_0;
            }
        }
    } else { // RUMBLEMANAGER_STATE_0
        for (i = 0; i < ARRAY_COUNT(rumbleMgr->unk_04); i++) {
            rumbleMgr->unk_04[i] = 0;
            rumbleMgr->unk_44[i] = 0;
            rumbleMgr->decreaseStep[i] = 0;
            rumbleMgr->unk_C4[i] = 0;
        }

        rumbleMgr->rumblingTimer = 0;
        rumbleMgr->unk_108 = 0;

        rumbleMgr->unk_10A = 0;
        rumbleMgr->unk_10B = 0;
        rumbleMgr->decreaseStepForced = 0;
        rumbleMgr->unk_10D = 0;

        func_80175434();
    }
}

void RumbleManager_Init(RumbleManager* rumbleMgr) {
    bzero(rumbleMgr, sizeof(RumbleManager));
    rumbleMgr->state = RUMBLEMANAGER_STATE_INITIAL;
    rumbleMgr->unk_105 = true;
}

void RumbleManager_Destroy(RumbleManager* rumbleMgr) {
}
