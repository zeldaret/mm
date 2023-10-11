#include "global.h"

#define NOW 0
#define None 0

typedef enum AnjuScheduleResult {
    /*  0 */ ANJU_SCH_NONE,
    /*  1 */ ANJU_SCH_1,
    /*  2 */ ANJU_SCH_2,
    /*  3 */ ANJU_SCH_3,
    /*  4 */ ANJU_SCH_4,
    /*  5 */ ANJU_SCH_5,
    /*  6 */ ANJU_SCH_6,
    /*  7 */ ANJU_SCH_7,
    /*  8 */ ANJU_SCH_8,
    /*  9 */ ANJU_SCH_9,
    /* 10 */ ANJU_SCH_A,
    /* 11 */ ANJU_SCH_B,
    /* 12 */ ANJU_SCH_C,
    /* 13 */ ANJU_SCH_D,
    /* 14 */ ANJU_SCH_E,
    /* 15 */ ANJU_SCH_F,
    /* 16 */ ANJU_SCH_10,
    /* 17 */ ANJU_SCH_11,
    /* 18 */ ANJU_SCH_12,
    /* 19 */ ANJU_SCH_13,
    /* 20 */ ANJU_SCH_14,
    /* 21 */ ANJU_SCH_15,
    /* 22 */ ANJU_SCH_16,
    /* 23 */ ANJU_SCH_17,
    /* 24 */ ANJU_SCH_18,
    /* 25 */ ANJU_SCH_19,
    /* 26 */ ANJU_SCH_1A,
    /* 27 */ ANJU_SCH_1B,
    /* 28 */ ANJU_SCH_1C,
    /* 29 */ ANJU_SCH_1D,
    /* 30 */ ANJU_SCH_1E,
    /* 31 */ ANJU_SCH_1F,
    /* 32 */ ANJU_SCH_20,
    /* 33 */ ANJU_SCH_21,
    /* 34 */ ANJU_SCH_22,
    /* 35 */ ANJU_SCH_23,
    /* 36 */ ANJU_SCH_24,
    /* 37 */ ANJU_SCH_25,
    /* 38 */ ANJU_SCH_26,
    /* 39 */ ANJU_SCH_27,
    /* 40 */ ANJU_SCH_28,
    /* 41 */ ANJU_SCH_29,
    /* 42 */ ANJU_SCH_2A,
    /* 43 */ ANJU_SCH_2B,
    /* 44 */ ANJU_SCH_2C,
    /* 45 */ ANJU_SCH_2D,
    /* 46 */ ANJU_SCH_2E,
    /* 47 */ ANJU_SCH_2F,
    /* 48 */ ANJU_SCH_30,
    /* 49 */ ANJU_SCH_31,
    /* 50 */ ANJU_SCH_32,
    /* 51 */ ANJU_SCH_33,
    /* 52 */ ANJU_SCH_34,
    /* 53 */ ANJU_SCH_35,
    /* 54 */ ANJU_SCH_36,
    /* 55 */ ANJU_SCH_37,
    /* 56 */ ANJU_SCH_38,
    /* 57 */ ANJU_SCH_39,
    /* 58 */ ANJU_SCH_3A,
    /* 59 */ ANJU_SCH_3B,
    /* 60 */ ANJU_SCH_3C,
    /* 61 */ ANJU_SCH_3D,
    /* 62 */ ANJU_SCH_3E,
    /* 63 */ ANJU_SCH_3F,
    /* 64 */ ANJU_SCH_MAX
} AnjuScheduleResult;

s32 scheduleScript(PlayState* play, ScheduleOutput* output) {
    if (gSaveContext.save.day == 1) {
        if (play->sceneId == SCENE_YADOYA) {
            if ((6, 0) <= NOW <= (10, 55)) {
                return ANJU_SCH_12, (6, 0), (10, 55);
            } else if ((10, 55) <= NOW <= (11, 10)) {
                return ANJU_SCH_28, (10, 55), (11, 10);
            } else if ((11, 10) <= NOW <= (11, 30)) {
                return ANJU_SCH_E, (11, 10), (11, 30);
            } else if ((11, 30) <= NOW <= (11, 50)) {
                return ANJU_SCH_2A, (11, 30), (11, 50);
            } else if ((11, 50) <= NOW <= (11, 55)) {
                return ANJU_SCH_1A, (11, 50), (11, 55);
            } else if ((11, 55) <= NOW <= (12, 0)) {
                return ANJU_SCH_2B, (11, 55), (12, 0);
            } else if ((12, 0) <= NOW <= (12, 15)) {
                return ANJU_SCH_15, (12, 0), (12, 15);
            } else if ((12, 15) <= NOW <= (12, 20)) {
                return ANJU_SCH_2C, (12, 15), (12, 20);
            } else if ((12, 20) <= NOW <= (12, 25)) {
                return ANJU_SCH_1B, (12, 20), (12, 25);
            } else if ((12, 25) <= NOW <= (12, 55)) {
                return ANJU_SCH_2D, (12, 25), (12, 55);
            } else if ((12, 55) <= NOW <= (13, 0)) {
                return ANJU_SCH_1C, (12, 55), (13, 0);
            } else if ((13, 15) <= NOW <= (13, 20)) {
                return ANJU_SCH_1D, (13, 15), (13, 20);
            } else if ((13, 20) <= NOW <= (13, 50)) {
                return ANJU_SCH_2E, (13, 20), (13, 50);
            } else if ((13, 50) <= NOW <= (14, 8)) {
                return ANJU_SCH_12, (13, 50), (14, 8);
            } else if ((14, 8) <= NOW <= (14, 18)) {
                return ANJU_SCH_10, (14, 8), (14, 18);
            } else if ((14, 18) <= NOW <= (16, 10)) {
                return ANJU_SCH_12, (14, 18), (16, 10);
            } else if ((16, 10) <= NOW <= (16, 30)) {
                return ANJU_SCH_11, (16, 10), (16, 30);
            } else if ((16, 30) <= NOW <= (19, 50)) {
                return ANJU_SCH_12, (16, 30), (19, 50);
            } else if ((19, 50) <= NOW <= (20, 20)) {
                return ANJU_SCH_2F, (19, 50), (20, 20);
            } else if ((20, 20) <= NOW <= (20, 30)) {
                return ANJU_SCH_13, (20, 20), (20, 30);
            } else if ((20, 30) <= NOW <= (21, 5)) {
                return ANJU_SCH_30, (20, 30), (21, 5);
            } else if ((21, 5) <= NOW <= (21, 10)) {
                return ANJU_SCH_1E, (21, 5), (21, 10);
            } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
                if ((23, 10) <= NOW <= (23, 15)) {
                    return ANJU_SCH_1F, (23, 10), (23, 15);
                } else if ((23, 15) <= NOW <= (0, 0)) {
                    return ANJU_SCH_31, (23, 15), (0, 0);
                } else if ((0, 0) <= NOW <= (6, 0)) {
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_HAD_MIDNIGHT_MEETING)) {
                        return None;
                    }
                    return ANJU_SCH_17, (0, 0), (6, 0);
                } else {
                    return None;
                }
            } else {
                return None;
            }
        } else {
            return None;
        }
    } else if (gSaveContext.save.day == 2) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_HAD_MIDNIGHT_MEETING)) {
            if (play->sceneId == SCENE_YADOYA) {
                if ((11, 3) <= NOW <= (11, 9)) {
                    return ANJU_SCH_20, (11, 3), (11, 9);
                } else if ((11, 9) <= NOW <= (11, 29)) {
                    return ANJU_SCH_32, (11, 9), (11, 29);
                } else if ((11, 29) <= NOW <= (11, 39)) {
                    return ANJU_SCH_21, (11, 29), (11, 39);
                } else if ((17, 24) <= NOW <= (17, 30)) {
                    return ANJU_SCH_22, (17, 24), (17, 30);
                } else if ((17, 30) <= NOW <= (17, 55)) {
                    return ANJU_SCH_33, (17, 30), (17, 55);
                } else if ((17, 55) <= NOW <= (18, 0)) {
                    return ANJU_SCH_23, (17, 55), (18, 0);
                } else if ((18, 0) <= NOW <= (19, 50)) {
                    return ANJU_SCH_12, (18, 0), (19, 50);
                } else if ((19, 50) <= NOW <= (20, 20)) {
                    return ANJU_SCH_2F, (19, 50), (20, 20);
                } else if ((20, 20) <= NOW <= (20, 30)) {
                    return ANJU_SCH_13, (20, 20), (20, 30);
                } else if ((20, 30) <= NOW <= (21, 0)) {
                    return ANJU_SCH_30, (20, 30), (21, 0);
                } else if ((21, 0) <= NOW <= (21, 5)) {
                    return ANJU_SCH_1E, (21, 0), (21, 5);
                } else if ((21, 30) <= NOW <= (23, 0)) {
                    return ANJU_SCH_18, (21, 30), (23, 0);
                } else {
                    return None;
                }
            } else if (play->sceneId == SCENE_TOWN) {
                if ((11, 29) <= NOW <= (11, 39)) {
                    return ANJU_SCH_25, (11, 29), (11, 39);
                } else if ((11, 39) <= NOW <= (12, 25)) {
                    return ANJU_SCH_36, (11, 39), (12, 25);
                } else if ((12, 25) <= NOW <= (13, 15)) {
                    return ANJU_SCH_37, (12, 25), (13, 15);
                } else if ((15, 55) <= NOW <= (16, 45)) {
                    return ANJU_SCH_3A, (15, 55), (16, 45);
                } else if ((16, 45) <= NOW <= (17, 24)) {
                    return ANJU_SCH_3B, (16, 45), (17, 24);
                } else if ((17, 24) <= NOW <= (17, 30)) {
                    return ANJU_SCH_26, (17, 24), (17, 30);
                } else {
                    return None;
                }
            } else if (play->sceneId == SCENE_CLOCKTOWER) {
                if ((11, 39) <= NOW <= (12, 25)) {
                    return ANJU_SCH_3C, (11, 39), (12, 25);
                } else if ((12, 25) <= NOW <= (13, 15)) {
                    return ANJU_SCH_3D, (12, 25), (13, 15);
                } else if ((15, 55) <= NOW <= (16, 45)) {
                    return ANJU_SCH_3E, (15, 55), (16, 45);
                } else if ((16, 45) <= NOW <= (17, 24)) {
                    return ANJU_SCH_3F, (16, 45), (17, 24);
                } else {
                    return None;
                }
            } else if (play->sceneId == SCENE_ALLEY) {
                if ((13, 15) <= NOW <= (13, 45)) {
                    return ANJU_SCH_38, (13, 15), (13, 45);
                } else if ((13, 45) <= NOW <= (15, 25)) {
                    return ANJU_SCH_3, (13, 45), (15, 25);
                } else if ((15, 25) <= NOW <= (15, 55)) {
                    return ANJU_SCH_39, (15, 25), (15, 55);
                } else {
                    return None;
                }
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_YADOYA) {
            if ((6, 0) <= NOW <= (10, 55)) {
                return ANJU_SCH_12, (6, 0), (10, 55);
            } else if ((10, 55) <= NOW <= (11, 10)) {
                return ANJU_SCH_28, (10, 55), (11, 10);
            } else if ((11, 10) <= NOW <= (11, 30)) {
                return ANJU_SCH_E, (11, 10), (11, 30);
            } else if ((11, 30) <= NOW <= (11, 50)) {
                return ANJU_SCH_2A, (11, 30), (11, 50);
            } else if ((11, 50) <= NOW <= (11, 55)) {
                return ANJU_SCH_1A, (11, 50), (11, 55);
            } else if ((11, 55) <= NOW <= (12, 0)) {
                return ANJU_SCH_2B, (11, 55), (12, 0);
            } else if ((12, 0) <= NOW <= (12, 15)) {
                return ANJU_SCH_15, (12, 0), (12, 15);
            } else if ((12, 15) <= NOW <= (12, 20)) {
                return ANJU_SCH_2C, (12, 15), (12, 20);
            } else if ((12, 20) <= NOW <= (12, 25)) {
                return ANJU_SCH_1B, (12, 20), (12, 25);
            } else if ((12, 25) <= NOW <= (12, 55)) {
                return ANJU_SCH_2D, (12, 25), (12, 55);
            } else if ((12, 55) <= NOW <= (13, 0)) {
                return ANJU_SCH_1C, (12, 55), (13, 0);
            } else if ((13, 15) <= NOW <= (13, 20)) {
                return ANJU_SCH_1D, (13, 15), (13, 20);
            } else if ((13, 20) <= NOW <= (13, 50)) {
                return ANJU_SCH_2E, (13, 20), (13, 50);
            } else if ((13, 50) <= NOW <= (19, 50)) {
                return ANJU_SCH_12, (13, 50), (19, 50);
            } else if ((19, 50) <= NOW <= (20, 20)) {
                return ANJU_SCH_2F, (19, 50), (20, 20);
            } else if ((20, 20) <= NOW <= (20, 30)) {
                return ANJU_SCH_13, (20, 20), (20, 30);
            } else if ((20, 30) <= NOW <= (21, 5)) {
                return ANJU_SCH_30, (20, 30), (21, 5);
            } else if ((21, 5) <= NOW <= (21, 10)) {
                return ANJU_SCH_1E, (21, 5), (21, 10);
            } else if ((21, 30) <= NOW <= (23, 0)) {
                return ANJU_SCH_18, (21, 30), (23, 0);
            } else {
                return None;
            }
        } else {
            return None;
        }
    } else if (gSaveContext.save.day == 3) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES)) {
            if (play->sceneId == SCENE_YADOYA) {
                if ((6, 0) <= NOW <= (11, 0)) {
                    return ANJU_SCH_16, (6, 0), (11, 0);
                } else if ((11, 0) <= NOW <= (11, 25)) {
                    return ANJU_SCH_34, (11, 0), (11, 25);
                } else if ((11, 25) <= NOW <= (11, 30)) {
                    return ANJU_SCH_24, (11, 25), (11, 30);
                } else if ((11, 30) <= NOW <= (11, 50)) {
                    return ANJU_SCH_35, (11, 30), (11, 50);
                } else if ((11, 50) <= NOW <= (12, 0)) {
                    return ANJU_SCH_27, (11, 50), (12, 0);
                } else if ((18, 0) <= NOW <= (5, 0)) {
                    return ANJU_SCH_1, (18, 0), (5, 0);
                } else if ((5, 0) <= NOW <= (6, 0)) {
                    return ANJU_SCH_1, (5, 0), (6, 0);
                } else {
                    return None;
                }
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_YADOYA) {
            if ((6, 0) <= NOW <= (11, 0)) {
                return ANJU_SCH_16, (6, 0), (11, 0);
            } else if ((11, 0) <= NOW <= (11, 25)) {
                return ANJU_SCH_34, (11, 0), (11, 25);
            } else if ((11, 25) <= NOW <= (11, 30)) {
                return ANJU_SCH_24, (11, 25), (11, 30);
            } else if ((11, 30) <= NOW <= (11, 50)) {
                return ANJU_SCH_35, (11, 30), (11, 50);
            } else if ((11, 50) <= NOW <= (12, 0)) {
                return ANJU_SCH_27, (11, 50), (12, 0);
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_OMOYA) {
            if ((18, 0) <= NOW <= (6, 0)) {
                return ANJU_SCH_C, (18, 0), (6, 0);
            } else {
                return None;
            }
        } else {
            return None;
        }
    } else {
        return None;
    }
}
