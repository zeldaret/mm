#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include "global.h"
#include "z64door.h"
#include "objects/gameplay_keep/gameplay_keep.h"

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor*, PlayState*);

#define ENDOOR_GET_TYPE(thisx) (((thisx)->params >> 7) & 7)
#define ENDOOR_GET_ACTION_VAR(thisx) (((thisx)->params) & 0x7F)

typedef enum EnDoorType {
    /* 0 */ ENDOOR_TYPE_0,
    /* 1 */ ENDOOR_TYPE_LOCKED,
    /* 2 */ ENDOOR_TYPE_2,
    /* 3 */ ENDOOR_TYPE_3,
    /* 4 */ ENDOOR_TYPE_4, // OoT: AJAR.
    /* 5 */ ENDOOR_TYPE_SCHEDULE,
    /* 6 */ ENDOOR_TYPE_6, // unreferenced
    /* 7 */ ENDOOR_TYPE_7 // unused
} EnDoorType;

typedef enum EnDoorScheduleType {
    /*  0 */ ENDOOR_SCH_TYPE_0,
    /*  1 */ ENDOOR_SCH_TYPE_1,
    /*  2 */ ENDOOR_SCH_TYPE_2,
    /*  3 */ ENDOOR_SCH_TYPE_3,
    /*  4 */ ENDOOR_SCH_TYPE_4,
    /*  5 */ ENDOOR_SCH_TYPE_5,
    /*  6 */ ENDOOR_SCH_TYPE_6,
    /*  7 */ ENDOOR_SCH_TYPE_7,
    /*  8 */ ENDOOR_SCH_TYPE_8,
    /*  9 */ ENDOOR_SCH_TYPE_9,
    /* 10 */ ENDOOR_SCH_TYPE_10,
    /* 11 */ ENDOOR_SCH_TYPE_11,
    /* 12 */ ENDOOR_SCH_TYPE_12,
    /* 13 */ ENDOOR_SCH_TYPE_13,
    /* 14 */ ENDOOR_SCH_TYPE_14,
    /* 15 */ ENDOOR_SCH_TYPE_15,
    /* 16 */ ENDOOR_SCH_TYPE_16,
    /* 17 */ ENDOOR_SCH_TYPE_17,
    /* 18 */ ENDOOR_SCH_TYPE_18,
    /* 19 */ ENDOOR_SCH_TYPE_19,
    /* 20 */ ENDOOR_SCH_TYPE_20,
    /* 21 */ ENDOOR_SCH_TYPE_21,
    /* 22 */ ENDOOR_SCH_TYPE_22,
    /* 23 */ ENDOOR_SCH_TYPE_23,
    /* 24 */ ENDOOR_SCH_TYPE_24,
    /* 25 */ ENDOOR_SCH_TYPE_25,
    /* 26 */ ENDOOR_SCH_TYPE_26,
    /* 27 */ ENDOOR_SCH_TYPE_27,
    /* 28 */ ENDOOR_SCH_TYPE_28,
    /* 29 */ ENDOOR_SCH_TYPE_29,
    /* 30 */ ENDOOR_SCH_TYPE_30,
    /* 31 */ ENDOOR_SCH_TYPE_31,
    /* 32 */ ENDOOR_SCH_TYPE_MAX
} EnDoorScheduleType;

typedef struct EnDoor {
    /* 0x000 */ KnobDoorActor knobDoor;
    /* 0x1A4 */ u8 doorType; // EnDoorType enum
    /* 0x1A5 */ union {
                    u8 actionVar; // generic
                    u8 actionVar_0_2_3; // ENDOOR_TYPE_0, ENDOOR_TYPE_2 and ENDOOR_TYPE_3
                    u8 switchFlag; // ENDOOR_TYPE_LOCKED
                    u8 schType; // ENDOOR_TYPE_SCHEDULE
                    u8 actionVar_7; // ENDOOR_TYPE_7
                } actionVar; // TODO: think on a better name
    /* 0x1A6 */ u8 lockTimer; // Used by ENDOOR_TYPE_LOCKED. Also controls drawing the lock on the door and side effects of opening a locked door, like decreasing the key count and updating the switch flag
    /* 0x1A7 */ s8 openTimer; // For how long the door will be open. positive/negative means the opening direction. It is meant to be used only by ENDOOR_TYPE_SCHEDULE, and set by schedule actors. See EnDoor_OpenScheduleActor.
    /* 0x1A8 */ Vec3s limbTable[DOOR_LIMB_MAX];
    /* 0x1C8 */ EnDoorActionFunc actionFunc;
} EnDoor;

#endif // Z_EN_DOOR_H
