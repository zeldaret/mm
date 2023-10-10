#include "global.h"

#define NOW 0

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

void scheduleScript(PlayState* play, ScheduleOutput* output) {
    /* 0x000 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(1, 0x151 - 0x005);
    if (gSaveContext.save.day == 1) {

        /* 0x005 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x150 - 0x00A);
        if (play->sceneId == SCENE_YADOYA) {

            /* 0x00A */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 10, 55, 0x14A - 0x011);
            if ((6, 0) <= NOW <= (10, 55)) {
                /* 0x14A */ SCHEDULE_CMD_RET_TIME(6, 0, 10, 55, ANJU_SCH_12);
                output->result = ANJU_SCH_12;
                output->time0 = (6, 0);
                output->time1 = (10, 55);
                output->hasResult = true;
                return;
            }

            /* 0x011 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(10, 55, 11, 10, 0x144 - 0x018);
            if ((10, 55) <= NOW <= (11, 10)) {
                /* 0x144 */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 10, ANJU_SCH_28);
                output->result = ANJU_SCH_28;
                output->time0 = (10, 55);
                output->time1 = (11, 10);
                output->hasResult = true;
                return;
            }
            /* 0x018 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 10, 11, 30, 0x13E - 0x01F);
            if ((11, 10) <= NOW <= (11, 30)) {
                /* 0x13E */ SCHEDULE_CMD_RET_TIME(11, 10, 11, 30, ANJU_SCH_E);
                output->result = ANJU_SCH_E;
                output->time0 = (11, 10);
                output->time1 = (11, 30);
                output->hasResult = true;
                return;
            }
            /* 0x01F */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 30, 11, 50, 0x138 - 0x026);
            if ((11, 30) <= NOW <= (11, 50)) {
                /* 0x138 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_2A);
                output->result = ANJU_SCH_2A;
                output->time0 = (11, 30);
                output->time1 = (11, 50);
                output->hasResult = true;
                return;
            }
            /* 0x026 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 50, 11, 55, 0x132 - 0x02D);
            if ((11, 50) <= NOW <= (11, 55)) {
                /* 0x132 */ SCHEDULE_CMD_RET_TIME(11, 50, 11, 55, ANJU_SCH_1A);
                output->result = ANJU_SCH_1A;
                output->time0 = (11, 50);
                output->time1 = (11, 55);
                output->hasResult = true;
                return;
            }
            /* 0x02D */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 55, 12, 0, 0x12C - 0x034);
            if ((11, 55) <= NOW <= (12, 0)) {
                /* 0x12C */ SCHEDULE_CMD_RET_TIME(11, 55, 12, 0, ANJU_SCH_2B);
                output->result = ANJU_SCH_2B;
                output->time0 = (11, 55);
                output->time1 = (12, 0);
                output->hasResult = true;
                return;
            }
            /* 0x034 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 0, 12, 15, 0x126 - 0x03B);
            if ((12, 0) <= NOW <= (12, 15)) {
                /* 0x126 */ SCHEDULE_CMD_RET_TIME(12, 0, 12, 15, ANJU_SCH_15);
                output->result = ANJU_SCH_15;
                output->time0 = (12, 0);
                output->time1 = (12, 15);
                output->hasResult = true;
                return;
            }
            /* 0x03B */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 15, 12, 20, 0x120 - 0x042);
            if ((12, 15) <= NOW <= (12, 20)) {
                /* 0x120 */ SCHEDULE_CMD_RET_TIME(12, 15, 12, 20, ANJU_SCH_2C);
                output->result = ANJU_SCH_2C;
                output->time0 = (12, 15);
                output->time1 = (12, 20);
                output->hasResult = true;
                return;
            }
            /* 0x042 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 20, 12, 25, 0x11A - 0x049);
            if ((12, 20) <= NOW <= (12, 25)) {
                /* 0x11A */ SCHEDULE_CMD_RET_TIME(12, 20, 12, 25, ANJU_SCH_1B);
                output->result = ANJU_SCH_1B;
                output->time0 = (12, 20);
                output->time1 = (12, 25);
                output->hasResult = true;
                return;
            }
            /* 0x049 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 25, 12, 55, 0x114 - 0x050);
            if ((12, 25) <= NOW <= (12, 55)) {
                /* 0x114 */ SCHEDULE_CMD_RET_TIME(12, 25, 12, 55, ANJU_SCH_2D);
                output->result = ANJU_SCH_2D;
                output->time0 = (12, 25);
                output->time1 = (12, 55);
                output->hasResult = true;
                return;
            }
            /* 0x050 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 55, 13, 0, 0x10E - 0x057);
            if ((12, 55) <= NOW <= (13, 0)) {
                /* 0x10E */ SCHEDULE_CMD_RET_TIME(12, 55, 13, 0, ANJU_SCH_1C);
                output->result = ANJU_SCH_1C;
                output->time0 = (12, 55);
                output->time1 = (13, 0);
                output->hasResult = true;
                return;
            }
            /* 0x057 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 15, 13, 20, 0x108 - 0x05E);
            if ((13, 15) <= NOW <= (13, 20)) {
                /* 0x108 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 20, ANJU_SCH_1D);
                output->result = ANJU_SCH_1D;
                output->time0 = (13, 15);
                output->time1 = (13, 20);
                output->hasResult = true;
                return;
            }
            /* 0x05E */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 20, 13, 50, 0x102 - 0x065);
            if ((13, 20) <= NOW <= (13, 50)) {
                /* 0x102 */ SCHEDULE_CMD_RET_TIME(13, 20, 13, 50, ANJU_SCH_2E);
                output->result = ANJU_SCH_2E;
                output->time0 = (13, 20);
                output->time1 = (13, 50);
                output->hasResult = true;
                return;
            }
            /* 0x065 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 50, 14, 8, 0x0FC - 0x06C);
            if ((13, 50) <= NOW <= (14, 8)) {
                /* 0x0FC */ SCHEDULE_CMD_RET_TIME(13, 50, 14, 8, ANJU_SCH_12);
                output->result = ANJU_SCH_12;
                output->time0 = (13, 50);
                output->time1 = (14, 8);
                output->hasResult = true;
                return;
            }
            /* 0x06C */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(14, 8, 14, 18, 0x0F6 - 0x073);
            if ((14, 8) <= NOW <= (14, 18)) {
                /* 0x0F6 */ SCHEDULE_CMD_RET_TIME(14, 8, 14, 18, ANJU_SCH_10);
                output->result = ANJU_SCH_10;
                output->time0 = (14, 8);
                output->time1 = (14, 18);
                output->hasResult = true;
                return;
            }
            /* 0x073 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(14, 18, 16, 10, 0x0F0 - 0x079);
            if ((14, 18) <= NOW <= (16, 10)) {
                /* 0x0F0 */ SCHEDULE_CMD_RET_TIME(14, 18, 16, 10, ANJU_SCH_12);
                output->result = ANJU_SCH_12;
                output->time0 = (14, 18);
                output->time1 = (16, 10);
                output->hasResult = true;
                return;
            }
            /* 0x079 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 10, 16, 30, 0x0EA - 0x07F);
            if ((16, 10) <= NOW <= (16, 30)) {
                /* 0x0EA */ SCHEDULE_CMD_RET_TIME(16, 10, 16, 30, ANJU_SCH_11);
                output->result = ANJU_SCH_11;
                output->time0 = (16, 10);
                output->time1 = (16, 30);
                output->hasResult = true;
                return;
            }
            /* 0x07F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 30, 19, 50, 0x0E4 - 0x085);
            if ((16, 30) <= NOW <= (19, 50)) {
                /* 0x0E4 */ SCHEDULE_CMD_RET_TIME(16, 30, 19, 50, ANJU_SCH_12);
                output->result = ANJU_SCH_12;
                output->time0 = (16, 30);
                output->time1 = (19, 50);
                output->hasResult = true;
                return;
            }
            /* 0x085 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x0DE - 0x08B);
            if ((19, 50) <= NOW <= (20, 20)) {
                /* 0x0DE */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_2F);
                output->result = ANJU_SCH_2F;
                output->time0 = (19, 50);
                output->time1 = (20, 20);
                output->hasResult = true;
                return;
            }

            /* 0x08B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x0D8 - 0x091);
            if ((20, 20) <= NOW <= (20, 30)) {
                /* 0x0D8 */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_13);
                output->result = ANJU_SCH_13;
                output->time0 = (20, 20);
                output->time1 = (20, 30);
                output->hasResult = true;
                return;

            }

            /* 0x091 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 5, 0x0D2 - 0x097);
            if ((20, 30) <= NOW <= (21, 5)) {
                /* 0x0D2 */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 5, ANJU_SCH_30);
                output->result = ANJU_SCH_30;
                output->time0 = (20, 30);
                output->time1 = (21, 5);
                output->hasResult = true;
                return;
            }

            /* 0x097 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 5, 21, 10, 0x0CC - 0x09D);
            if ((21, 5) <= NOW <= (21, 10)) {
                /* 0x0CC */ SCHEDULE_CMD_RET_TIME(21, 5, 21, 10, ANJU_SCH_1E);
                output->result = ANJU_SCH_1E;
                output->time0 = (21, 5);
                output->time1 = (21, 10);
                output->hasResult = true;
                return;

            }

            /* 0x09D */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING, 0x0A2 - 0x0A1);
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
                /* 0x0A2 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(23, 10, 23, 15, 0x0C6 - 0x0A8);
                if ((23, 10) <= NOW <= (23, 15)) {

                    /* 0x0C6 */ SCHEDULE_CMD_RET_TIME(23, 10, 23, 15, ANJU_SCH_1F);
                    output->result = ANJU_SCH_1F;
                    output->time0 = (23, 10);
                    output->time1 = (23, 15);
                    output->hasResult = true;
                    return;

                }

                /* 0x0A8 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(23, 15, 0, 0, 0x0C0 - 0x0AE);
                if ((23, 15) <= NOW <= (0, 0)) {

                    /* 0x0C0 */ SCHEDULE_CMD_RET_TIME(23, 15, 0, 0, ANJU_SCH_31);
                    output->result = ANJU_SCH_31;
                    output->time0 = (23, 15);
                    output->time1 = (0, 0);
                    output->hasResult = true;
                    return;

                }

                /* 0x0AE */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 6, 0, 0x0B5 - 0x0B4);
                if (!((0, 0) <= NOW <= (6, 0))) {
                    /* 0x0B4 */ SCHEDULE_CMD_RET_NONE();
                    output->hasResult = false;
                    return;
                }

                /* 0x0B5 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x0BF - 0x0B9);
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_HAD_MIDNIGHT_MEETING)) {
                    /* 0x0BF */ SCHEDULE_CMD_RET_NONE();
                    output->hasResult = false;
                    return;
                }
                /* 0x0B9 */ SCHEDULE_CMD_RET_TIME(0, 0, 6, 0, ANJU_SCH_17);
                output->result = ANJU_SCH_17;
                output->time0 = (0, 0);
                output->time1 = (6, 0);
                output->hasResult = true;
                return;

            }

            /* 0x0A1 */ SCHEDULE_CMD_RET_NONE();
            output->hasResult = false;
            return;

        } else {
            goto label_150;
        }

    label_150:
        /* 0x150 */ SCHEDULE_CMD_RET_NONE();
        output->hasResult = false;
        return;

    } else {

        goto label_151;
    }

label_151:
    /* 0x151 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(2, 0x391 - 0x156);
    if (gSaveContext.save.day != 2) {
        goto label_391;
    }

    /* 0x156 */ SCHEDULE_CMD_CHECK_FLAG_L(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x29E - 0x15B);
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_HAD_MIDNIGHT_MEETING)) {
        goto label_29E;
    }

    /* 0x15B */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x1F2 - 0x160);
    if (play->sceneId != SCENE_YADOYA) {
        goto label_1F2;
    }

    /* 0x160 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 3, 11, 9, 0x1EC - 0x167);
    if ((11, 3) <= NOW <= (11, 9)) {
        goto label_1EC;
    }

    /* 0x167 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 9, 11, 29, 0x1E6 - 0x16D);
    if ((11, 9) <= NOW <= (11, 29)) {
        goto label_1E6;
    }

    /* 0x16D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 29, 11, 39, 0x1E0 - 0x173);
    if ((11, 29) <= NOW <= (11, 39)) {
        goto label_1E0;
    }

    /* 0x173 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 24, 17, 30, 0x1DA - 0x179);
    if ((17, 24) <= NOW <= (17, 30)) {
        goto label_1DA;
    }

    /* 0x179 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 30, 17, 55, 0x1D4 - 0x17F);
    if ((17, 30) <= NOW <= (17, 55)) {
        goto label_1D4;
    }

    /* 0x17F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 55, 18, 0, 0x1CE - 0x185);
    if ((17, 55) <= NOW <= (18, 0)) {
        goto label_1CE;
    }

    /* 0x185 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 19, 50, 0x1C8 - 0x18B);
    if ((18, 0) <= NOW <= (19, 50)) {
        goto label_1C8;
    }

    /* 0x18B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x1C2 - 0x191);
    if ((19, 50) <= NOW <= (20, 20)) {
        goto label_1C2;
    }

    /* 0x191 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x1BC - 0x197);
    if ((20, 20) <= NOW <= (20, 30)) {
        goto label_1BC;
    }

    /* 0x197 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 0, 0x1B6 - 0x19D);
    if ((20, 30) <= NOW <= (21, 0)) {
        goto label_1B6;
    }

    /* 0x19D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 21, 5, 0x1B0 - 0x1A3);
    if ((21, 0) <= NOW <= (21, 5)) {
        goto label_1B0;
    }

    /* 0x1A3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 30, 23, 0, 0x1AA - 0x1A9);
    if ((21, 30) <= NOW <= (23, 0)) {
        goto label_1AA;
    }

label_1A9:
    /* 0x1A9 */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_1AA:
    /* 0x1AA */ SCHEDULE_CMD_RET_TIME(21, 30, 23, 0, ANJU_SCH_18);
    output->result = ANJU_SCH_18;
    output->time0 = (21, 30);
    output->time1 = (23, 0);
    output->hasResult = true;
    return;

label_1B0:
    /* 0x1B0 */ SCHEDULE_CMD_RET_TIME(21, 0, 21, 5, ANJU_SCH_1E);
    output->result = ANJU_SCH_1E;
    output->time0 = (21, 0);
    output->time1 = (21, 5);
    output->hasResult = true;
    return;

label_1B6:
    /* 0x1B6 */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 0, ANJU_SCH_30);
    output->result = ANJU_SCH_30;
    output->time0 = (20, 30);
    output->time1 = (21, 0);
    output->hasResult = true;
    return;

label_1BC:
    /* 0x1BC */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_13);
    output->result = ANJU_SCH_13;
    output->time0 = (20, 20);
    output->time1 = (20, 30);
    output->hasResult = true;
    return;

label_1C2:
    /* 0x1C2 */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_2F);
    output->result = ANJU_SCH_2F;
    output->time0 = (19, 50);
    output->time1 = (20, 20);
    output->hasResult = true;
    return;

label_1C8:
    /* 0x1C8 */ SCHEDULE_CMD_RET_TIME(18, 0, 19, 50, ANJU_SCH_12);
    output->result = ANJU_SCH_12;
    output->time0 = (18, 0);
    output->time1 = (19, 50);
    output->hasResult = true;
    return;

label_1CE:
    /* 0x1CE */ SCHEDULE_CMD_RET_TIME(17, 55, 18, 0, ANJU_SCH_23);
    output->result = ANJU_SCH_23;
    output->time0 = (17, 55);
    output->time1 = (18, 0);
    output->hasResult = true;
    return;

label_1D4:
    /* 0x1D4 */ SCHEDULE_CMD_RET_TIME(17, 30, 17, 55, ANJU_SCH_33);
    output->result = ANJU_SCH_33;
    output->time0 = (17, 30);
    output->time1 = (17, 55);
    output->hasResult = true;
    return;

label_1DA:
    /* 0x1DA */ SCHEDULE_CMD_RET_TIME(17, 24, 17, 30, ANJU_SCH_22);
    output->result = ANJU_SCH_22;
    output->time0 = (17, 24);
    output->time1 = (17, 30);
    output->hasResult = true;
    return;

label_1E0:
    /* 0x1E0 */ SCHEDULE_CMD_RET_TIME(11, 29, 11, 39, ANJU_SCH_21);
    output->result = ANJU_SCH_21;
    output->time0 = (11, 29);
    output->time1 = (11, 39);
    output->hasResult = true;
    return;

label_1E6:
    /* 0x1E6 */ SCHEDULE_CMD_RET_TIME(11, 9, 11, 29, ANJU_SCH_32);
    output->result = ANJU_SCH_32;
    output->time0 = (11, 9);
    output->time1 = (11, 29);
    output->hasResult = true;
    return;

label_1EC:
    /* 0x1EC */ SCHEDULE_CMD_RET_TIME(11, 3, 11, 9, ANJU_SCH_20);
    output->result = ANJU_SCH_20;
    output->time0 = (11, 3);
    output->time1 = (11, 9);
    output->hasResult = true;
    return;

label_1F2:
    /* 0x1F2 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_TOWN, 0x23F - 0x1F6);
    if (play->sceneId != SCENE_TOWN) {
        goto label_23F;
    }

    /* 0x1F6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 29, 11, 39, 0x239 - 0x1FC);
    if ((11, 29) <= NOW <= (11, 39)) {
        goto label_239;
    }

    /* 0x1FC */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 39, 12, 25, 0x233 - 0x202);
    if ((11, 39) <= NOW <= (12, 25)) {
        goto label_233;
    }

    /* 0x202 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 13, 15, 0x22D - 0x208);
    if ((12, 25) <= NOW <= (13, 15)) {
        goto label_22D;
    }

    /* 0x208 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 55, 16, 45, 0x227 - 0x20E);
    if ((15, 55) <= NOW <= (16, 45)) {
        goto label_227;
    }

    /* 0x20E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 45, 17, 24, 0x221 - 0x214);
    if ((16, 45) <= NOW <= (17, 24)) {
        goto label_221;
    }

    /* 0x214 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 24, 17, 30, 0x21B - 0x21A);
    if ((17, 24) <= NOW <= (17, 30)) {
        goto label_21B;
    }

label_21A:
    /* 0x21A */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_21B:
    /* 0x21B */ SCHEDULE_CMD_RET_TIME(17, 24, 17, 30, ANJU_SCH_26);
    output->result = ANJU_SCH_26;
    output->time0 = (17, 24);
    output->time1 = (17, 30);
    output->hasResult = true;
    return;

label_221:
    /* 0x221 */ SCHEDULE_CMD_RET_TIME(16, 45, 17, 24, ANJU_SCH_3B);
    output->result = ANJU_SCH_3B;
    output->time0 = (16, 45);
    output->time1 = (17, 24);
    output->hasResult = true;
    return;

label_227:
    /* 0x227 */ SCHEDULE_CMD_RET_TIME(15, 55, 16, 45, ANJU_SCH_3A);
    output->result = ANJU_SCH_3A;
    output->time0 = (15, 55);
    output->time1 = (16, 45);
    output->hasResult = true;
    return;

label_22D:
    /* 0x22D */ SCHEDULE_CMD_RET_TIME(12, 25, 13, 15, ANJU_SCH_37);
    output->result = ANJU_SCH_37;
    output->time0 = (12, 25);
    output->time1 = (13, 15);
    output->hasResult = true;
    return;

label_233:
    /* 0x233 */ SCHEDULE_CMD_RET_TIME(11, 39, 12, 25, ANJU_SCH_36);
    output->result = ANJU_SCH_36;
    output->time0 = (11, 39);
    output->time1 = (12, 25);
    output->hasResult = true;
    return;

label_239:
    /* 0x239 */ SCHEDULE_CMD_RET_TIME(11, 29, 11, 39, ANJU_SCH_25);
    output->result = ANJU_SCH_25;
    output->time0 = (11, 29);
    output->time1 = (11, 39);
    output->hasResult = true;
    return;

label_23F:
    /* 0x23F */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_CLOCKTOWER, 0x274 - 0x243);
    if (play->sceneId != SCENE_CLOCKTOWER) {
        goto label_274;
    }

    /* 0x243 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 39, 12, 25, 0x26E - 0x249);
    if ((11, 39) <= NOW <= (12, 25)) {
        goto label_26E;
    }

    /* 0x249 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 13, 15, 0x268 - 0x24F);
    if ((12, 25) <= NOW <= (13, 15)) {
        goto label_268;
    }

    /* 0x24F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 55, 16, 45, 0x262 - 0x255);
    if ((15, 55) <= NOW <= (16, 45)) {
        goto label_262;
    }

    /* 0x255 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 45, 17, 24, 0x25C - 0x25B);
    if ((16, 45) <= NOW <= (17, 24)) {
        goto label_25C;
    }

label_25B:
    /* 0x25B */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_25C:
    /* 0x25C */ SCHEDULE_CMD_RET_TIME(16, 45, 17, 24, ANJU_SCH_3F);
    output->result = ANJU_SCH_3F;
    output->time0 = (16, 45);
    output->time1 = (17, 24);
    output->hasResult = true;
    return;

label_262:
    /* 0x262 */ SCHEDULE_CMD_RET_TIME(15, 55, 16, 45, ANJU_SCH_3E);
    output->result = ANJU_SCH_3E;
    output->time0 = (15, 55);
    output->time1 = (16, 45);
    output->hasResult = true;
    return;

label_268:
    /* 0x268 */ SCHEDULE_CMD_RET_TIME(12, 25, 13, 15, ANJU_SCH_3D);
    output->result = ANJU_SCH_3D;
    output->time0 = (12, 25);
    output->time1 = (13, 15);
    output->hasResult = true;
    return;

label_26E:
    /* 0x26E */ SCHEDULE_CMD_RET_TIME(11, 39, 12, 25, ANJU_SCH_3C);
    output->result = ANJU_SCH_3C;
    output->time0 = (11, 39);
    output->time1 = (12, 25);
    output->hasResult = true;
    return;

label_274:
    /* 0x274 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_ALLEY, 0x29D - 0x278);
    if (play->sceneId != SCENE_ALLEY) {
        goto label_29D;
    }

    /* 0x278 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 15, 13, 45, 0x297 - 0x27E);
    if ((13, 15) <= NOW <= (13, 45)) {
        goto label_297;
    }

    /* 0x27E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 45, 15, 25, 0x291 - 0x284);
    if ((13, 45) <= NOW <= (15, 25)) {
        goto label_291;
    }

    /* 0x284 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 25, 15, 55, 0x28B - 0x28A);
    if ((15, 25) <= NOW <= (15, 55)) {
        goto label_28B;
    }

label_28A:
    /* 0x28A */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_28B:
    /* 0x28B */ SCHEDULE_CMD_RET_TIME(15, 25, 15, 55, ANJU_SCH_39);
    output->result = ANJU_SCH_39;
    output->time0 = (15, 25);
    output->time1 = (15, 55);
    output->hasResult = true;
    return;

label_291:
    /* 0x291 */ SCHEDULE_CMD_RET_TIME(13, 45, 15, 25, ANJU_SCH_3);
    output->result = ANJU_SCH_3;
    output->time0 = (13, 45);
    output->time1 = (15, 25);
    output->hasResult = true;
    return;

label_297:
    /* 0x297 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 45, ANJU_SCH_38);
    output->result = ANJU_SCH_38;
    output->time0 = (13, 15);
    output->time1 = (13, 45);
    output->hasResult = true;
    return;

label_29D:
    /* 0x29D */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_29E:
    /* 0x29E */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x390 - 0x2A3);
    if (play->sceneId != SCENE_YADOYA) {
        goto label_390;
    }

    /* 0x2A3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 10, 55, 0x38A - 0x2AA);
    if ((6, 0) <= NOW <= (10, 55)) {
        goto label_38A;
    }

    /* 0x2AA */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(10, 55, 11, 10, 0x384 - 0x2B1);
    if ((10, 55) <= NOW <= (11, 10)) {
        goto label_384;
    }

    /* 0x2B1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 10, 11, 30, 0x37E - 0x2B8);
    if ((11, 10) <= NOW <= (11, 30)) {
        goto label_37E;
    }

    /* 0x2B8 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 30, 11, 50, 0x378 - 0x2BF);
    if ((11, 30) <= NOW <= (11, 50)) {
        goto label_378;
    }

    /* 0x2BF */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 50, 11, 55, 0x372 - 0x2C6);
    if ((11, 50) <= NOW <= (11, 55)) {
        goto label_372;
    }

    /* 0x2C6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 55, 12, 0, 0x36C - 0x2CD);
    if ((11, 55) <= NOW <= (12, 0)) {
        goto label_36C;
    }

    /* 0x2CD */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 0, 12, 15, 0x366 - 0x2D4);
    if ((12, 0) <= NOW <= (12, 15)) {
        goto label_366;
    }

    /* 0x2D4 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 15, 12, 20, 0x360 - 0x2DB);
    if ((12, 15) <= NOW <= (12, 20)) {
        goto label_360;
    }

    /* 0x2DB */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 20, 12, 25, 0x35A - 0x2E1);
    if ((12, 20) <= NOW <= (12, 25)) {
        goto label_35A;
    }

    /* 0x2E1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 12, 55, 0x354 - 0x2E7);
    if ((12, 25) <= NOW <= (12, 55)) {
        goto label_354;
    }

    /* 0x2E7 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 55, 13, 0, 0x34E - 0x2ED);
    if ((12, 55) <= NOW <= (13, 0)) {
        goto label_34E;
    }

    /* 0x2ED */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 15, 13, 20, 0x348 - 0x2F3);
    if ((13, 15) <= NOW <= (13, 20)) {
        goto label_348;
    }

    /* 0x2F3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 20, 13, 50, 0x342 - 0x2F9);
    if ((13, 20) <= NOW <= (13, 50)) {
        goto label_342;
    }

    /* 0x2F9 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 50, 19, 50, 0x33C - 0x2FF);
    if ((13, 50) <= NOW <= (19, 50)) {
        goto label_33C;
    }

    /* 0x2FF */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x336 - 0x305);
    if ((19, 50) <= NOW <= (20, 20)) {
        goto label_336;
    }

    /* 0x305 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x330 - 0x30B);
    if ((20, 20) <= NOW <= (20, 30)) {
        goto label_330;
    }

    /* 0x30B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 5, 0x32A - 0x311);
    if ((20, 30) <= NOW <= (21, 5)) {
        goto label_32A;
    }

    /* 0x311 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 5, 21, 10, 0x324 - 0x317);
    if ((21, 5) <= NOW <= (21, 10)) {
        goto label_324;
    }

    /* 0x317 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 30, 23, 0, 0x31E - 0x31D);
    if ((21, 30) <= NOW <= (23, 0)) {
        goto label_31E;
    }

label_31D:
    /* 0x31D */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_31E:
    /* 0x31E */ SCHEDULE_CMD_RET_TIME(21, 30, 23, 0, ANJU_SCH_18);
    output->result = ANJU_SCH_18;
    output->time0 = (21, 30);
    output->time1 = (23, 0);
    output->hasResult = true;
    return;

label_324:
    /* 0x324 */ SCHEDULE_CMD_RET_TIME(21, 5, 21, 10, ANJU_SCH_1E);
    output->result = ANJU_SCH_1E;
    output->time0 = (21, 5);
    output->time1 = (21, 10);
    output->hasResult = true;
    return;

label_32A:
    /* 0x32A */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 5, ANJU_SCH_30);
    output->result = ANJU_SCH_30;
    output->time0 = (20, 30);
    output->time1 = (21, 5);
    output->hasResult = true;
    return;

label_330:
    /* 0x330 */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_13);
    output->result = ANJU_SCH_13;
    output->time0 = (20, 20);
    output->time1 = (20, 30);
    output->hasResult = true;
    return;

label_336:
    /* 0x336 */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_2F);
    output->result = ANJU_SCH_2F;
    output->time0 = (19, 50);
    output->time1 = (20, 20);
    output->hasResult = true;
    return;

label_33C:
    /* 0x33C */ SCHEDULE_CMD_RET_TIME(13, 50, 19, 50, ANJU_SCH_12);
    output->result = ANJU_SCH_12;
    output->time0 = (13, 50);
    output->time1 = (19, 50);
    output->hasResult = true;
    return;

label_342:
    /* 0x342 */ SCHEDULE_CMD_RET_TIME(13, 20, 13, 50, ANJU_SCH_2E);
    output->result = ANJU_SCH_2E;
    output->time0 = (13, 20);
    output->time1 = (13, 50);
    output->hasResult = true;
    return;

label_348:
    /* 0x348 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 20, ANJU_SCH_1D);
    output->result = ANJU_SCH_1D;
    output->time0 = (13, 15);
    output->time1 = (13, 20);
    output->hasResult = true;
    return;

label_34E:
    /* 0x34E */ SCHEDULE_CMD_RET_TIME(12, 55, 13, 0, ANJU_SCH_1C);
    output->result = ANJU_SCH_1C;
    output->time0 = (12, 55);
    output->time1 = (13, 0);
    output->hasResult = true;
    return;

label_354:
    /* 0x354 */ SCHEDULE_CMD_RET_TIME(12, 25, 12, 55, ANJU_SCH_2D);
    output->result = ANJU_SCH_2D;
    output->time0 = (12, 25);
    output->time1 = (12, 55);
    output->hasResult = true;
    return;

label_35A:
    /* 0x35A */ SCHEDULE_CMD_RET_TIME(12, 20, 12, 25, ANJU_SCH_1B);
    output->result = ANJU_SCH_1B;
    output->time0 = (12, 20);
    output->time1 = (12, 25);
    output->hasResult = true;
    return;

label_360:
    /* 0x360 */ SCHEDULE_CMD_RET_TIME(12, 15, 12, 20, ANJU_SCH_2C);
    output->result = ANJU_SCH_2C;
    output->time0 = (12, 15);
    output->time1 = (12, 20);
    output->hasResult = true;
    return;

label_366:
    /* 0x366 */ SCHEDULE_CMD_RET_TIME(12, 0, 12, 15, ANJU_SCH_15);
    output->result = ANJU_SCH_15;
    output->time0 = (12, 0);
    output->time1 = (12, 15);
    output->hasResult = true;
    return;

label_36C:
    /* 0x36C */ SCHEDULE_CMD_RET_TIME(11, 55, 12, 0, ANJU_SCH_2B);
    output->result = ANJU_SCH_2B;
    output->time0 = (11, 55);
    output->time1 = (12, 0);
    output->hasResult = true;
    return;

label_372:
    /* 0x372 */ SCHEDULE_CMD_RET_TIME(11, 50, 11, 55, ANJU_SCH_1A);
    output->result = ANJU_SCH_1A;
    output->time0 = (11, 50);
    output->time1 = (11, 55);
    output->hasResult = true;
    return;

label_378:
    /* 0x378 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_2A);
    output->result = ANJU_SCH_2A;
    output->time0 = (11, 30);
    output->time1 = (11, 50);
    output->hasResult = true;
    return;

label_37E:
    /* 0x37E */ SCHEDULE_CMD_RET_TIME(11, 10, 11, 30, ANJU_SCH_E);
    output->result = ANJU_SCH_E;
    output->time0 = (11, 10);
    output->time1 = (11, 30);
    output->hasResult = true;
    return;

label_384:
    /* 0x384 */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 10, ANJU_SCH_28);
    output->result = ANJU_SCH_28;
    output->time0 = (10, 55);
    output->time1 = (11, 10);
    output->hasResult = true;
    return;

label_38A:
    /* 0x38A */ SCHEDULE_CMD_RET_TIME(6, 0, 10, 55, ANJU_SCH_12);
    output->result = ANJU_SCH_12;
    output->time0 = (6, 0);
    output->time1 = (10, 55);
    output->hasResult = true;
    return;

label_390:
    /* 0x390 */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_391:
    /* 0x391 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(3, 0x447 - 0x396);
    if (gSaveContext.save.day != 3) {
        goto label_447;
    }

    /* 0x396 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES, 0x3ED - 0x39A);
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES)) {
        goto label_3ED;
    }

    /* 0x39A */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x3DB - 0x39E);
    if (play->sceneId != SCENE_YADOYA) {
        goto label_3DB;
    }

    /* 0x39E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 11, 0, 0x3D5 - 0x3A4);
    if ((6, 0) <= NOW <= (11, 0)) {
        goto label_3D5;
    }

    /* 0x3A4 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 0, 11, 25, 0x3CF - 0x3AA);
    if ((11, 0) <= NOW <= (11, 25)) {
        goto label_3CF;
    }

    /* 0x3AA */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 25, 11, 30, 0x3C9 - 0x3B0);
    if ((11, 25) <= NOW <= (11, 30)) {
        goto label_3C9;
    }

    /* 0x3B0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 30, 11, 50, 0x3C3 - 0x3B6);
    if ((11, 30) <= NOW <= (11, 50)) {
        goto label_3C3;
    }

    /* 0x3B6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 50, 12, 0, 0x3BD - 0x3BC);
    if ((11, 50) <= NOW <= (12, 0)) {
        goto label_3BD;
    }

label_3BC:
    /* 0x3BC */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_3BD:
    /* 0x3BD */ SCHEDULE_CMD_RET_TIME(11, 50, 12, 0, ANJU_SCH_27);
    output->result = ANJU_SCH_27;
    output->time0 = (11, 50);
    output->time1 = (12, 0);
    output->hasResult = true;
    return;

label_3C3:
    /* 0x3C3 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_35);
    output->result = ANJU_SCH_35;
    output->time0 = (11, 30);
    output->time1 = (11, 50);
    output->hasResult = true;
    return;

label_3C9:
    /* 0x3C9 */ SCHEDULE_CMD_RET_TIME(11, 25, 11, 30, ANJU_SCH_24);
    output->result = ANJU_SCH_24;
    output->time0 = (11, 25);
    output->time1 = (11, 30);
    output->hasResult = true;
    return;

label_3CF:
    /* 0x3CF */ SCHEDULE_CMD_RET_TIME(11, 0, 11, 25, ANJU_SCH_34);
    output->result = ANJU_SCH_34;
    output->time0 = (11, 0);
    output->time1 = (11, 25);
    output->hasResult = true;
    return;

label_3D5:
    /* 0x3D5 */ SCHEDULE_CMD_RET_TIME(6, 0, 11, 0, ANJU_SCH_16);
    output->result = ANJU_SCH_16;
    output->time0 = (6, 0);
    output->time1 = (11, 0);
    output->hasResult = true;
    return;

label_3DB:
    /* 0x3DB */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x3EC - 0x3DF);
    if (play->sceneId != SCENE_OMOYA) {
        goto label_3EC;
    }

    /* 0x3DF */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 6, 0, 0x3E6 - 0x3E5);
    if ((18, 0) <= NOW <= (6, 0)) {
        goto label_3E6;
    }

label_3E5:
    /* 0x3E5 */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_3E6:
    /* 0x3E6 */ SCHEDULE_CMD_RET_TIME(18, 0, 6, 0, ANJU_SCH_C);
    output->result = ANJU_SCH_C;
    output->time0 = (18, 0);
    output->time1 = (6, 0);
    output->hasResult = true;
    return;

label_3EC:
    /* 0x3EC */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_3ED:
    /* 0x3ED */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x446 - 0x3F1);
    if (play->sceneId != SCENE_YADOYA) {
        goto label_446;
    }

    /* 0x3F1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 11, 0, 0x440 - 0x3F7);
    if ((6, 0) <= NOW <= (11, 0)) {
        goto label_440;
    }

    /* 0x3F7 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 0, 11, 25, 0x43A - 0x3FD);
    if ((11, 0) <= NOW <= (11, 25)) {
        goto label_43A;
    }

    /* 0x3FD */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 25, 11, 30, 0x434 - 0x403);
    if ((11, 25) <= NOW <= (11, 30)) {
        goto label_434;
    }

    /* 0x403 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 30, 11, 50, 0x42E - 0x409);
    if ((11, 30) <= NOW <= (11, 50)) {
        goto label_42E;
    }

    /* 0x409 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 50, 12, 0, 0x428 - 0x40F);
    if ((11, 50) <= NOW <= (12, 0)) {
        goto label_428;
    }

    /* 0x40F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 5, 0, 0x422 - 0x415);
    if ((18, 0) <= NOW <= (5, 0)) {
        goto label_422;
    }

    /* 0x415 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(5, 0, 6, 0, 0x41C - 0x41B);
    if ((5, 0) <= NOW <= (6, 0)) {
        goto label_41C;
    }

label_41B:
    /* 0x41B */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_41C:
    /* 0x41C */ SCHEDULE_CMD_RET_TIME(5, 0, 6, 0, ANJU_SCH_1);
    output->result = ANJU_SCH_1;
    output->time0 = (5, 0);
    output->time1 = (6, 0);
    output->hasResult = true;
    return;

label_422:
    /* 0x422 */ SCHEDULE_CMD_RET_TIME(18, 0, 5, 0, ANJU_SCH_1);
    output->result = ANJU_SCH_1;
    output->time0 = (18, 0);
    output->time1 = (5, 0);
    output->hasResult = true;
    return;

label_428:
    /* 0x428 */ SCHEDULE_CMD_RET_TIME(11, 50, 12, 0, ANJU_SCH_27);
    output->result = ANJU_SCH_27;
    output->time0 = (11, 50);
    output->time1 = (12, 0);
    output->hasResult = true;
    return;

label_42E:
    /* 0x42E */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_35);
    output->result = ANJU_SCH_35;
    output->time0 = (11, 30);
    output->time1 = (11, 50);
    output->hasResult = true;
    return;

label_434:
    /* 0x434 */ SCHEDULE_CMD_RET_TIME(11, 25, 11, 30, ANJU_SCH_24);
    output->result = ANJU_SCH_24;
    output->time0 = (11, 25);
    output->time1 = (11, 30);
    output->hasResult = true;
    return;

label_43A:
    /* 0x43A */ SCHEDULE_CMD_RET_TIME(11, 0, 11, 25, ANJU_SCH_34);
    output->result = ANJU_SCH_34;
    output->time0 = (11, 0);
    output->time1 = (11, 25);
    output->hasResult = true;
    return;

label_440:
    /* 0x440 */ SCHEDULE_CMD_RET_TIME(6, 0, 11, 0, ANJU_SCH_16);
    output->result = ANJU_SCH_16;
    output->time0 = (6, 0);
    output->time1 = (11, 0);
    output->hasResult = true;
    return;

label_446:
    /* 0x446 */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;

label_447:
    /* 0x447 */ SCHEDULE_CMD_RET_NONE();
    output->hasResult = false;
    return;


}
