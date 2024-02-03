#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include "global.h"
#include "z64door.h"
#include "objects/gameplay_keep/gameplay_keep.h"

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor*, PlayState*);

typedef enum EnDoorType {
    /* 0 */ ENDOOR_TYPE_0,
    /* 1 */ ENDOOR_TYPE_LOCKED,
    /* 2 */ ENDOOR_TYPE_2, // Unused
    /* 3 */ ENDOOR_TYPE_3, // Checks if current time is night and tells the Player the Shop/Store/Whatever is closed and gives a custom message for each kind of building. Used, but all uses makes the door behave like a normal door
    /* 4 */ ENDOOR_TYPE_4, // OoT: AJAR. unused
    /* 5 */ ENDOOR_TYPE_SCHEDULE,
    /* 6 */ ENDOOR_TYPE_6, // unreferenced
    /* 7 */ ENDOOR_TYPE_7 // unused
} EnDoorType;

typedef enum EnDoorScheduleType {
    /*  0 */ ENDOOR_SCH_TYPE_SWORDSMANS_SCHOOL,
    /*  1 */ ENDOOR_SCH_TYPE_POST_OFFICE,
    /*  2 */ ENDOOR_SCH_TYPE_LOTTERY_SHOP,
    /*  3 */ ENDOOR_SCH_TYPE_TRADING_POST,
    /*  4 */ ENDOOR_SCH_TYPE_CURIOSITY_SHOP,
    /*  5 */ ENDOOR_SCH_TYPE_LAUNDRY_POOL,
    /*  6 */ ENDOOR_SCH_TYPE_BOMB_SHOP,
    /*  7 */ ENDOOR_SCH_TYPE_TOWN_SHOOTING_GALLERY,
    /*  8 */ ENDOOR_SCH_TYPE_TREASURE_CHEST_SHOP,
    /*  9 */ ENDOOR_SCH_TYPE_HONEY_DARLING_SHOP,
    /* 10 */ ENDOOR_SCH_TYPE_MILK_BAR,
    /* 11 */ ENDOOR_SCH_TYPE_INN_MAIN_DOOR, // MAIN_ENTRANCE?
    /* 12 */ ENDOOR_SCH_TYPE_INN_UPPER_ENTRANCE,
    /* 13 */ ENDOOR_SCH_TYPE_INN_GRANNYS_DOOR,
    /* 14 */ ENDOOR_SCH_TYPE_INN_STAFF_ROOM_DOOR,
    /* 15 */ ENDOOR_SCH_TYPE_INN_KNIFE_CHAMBER_DOOR,
    /* 16 */ ENDOOR_SCH_TYPE_INN_LARGE_SUITE_DOOR,
    /* 17 */ ENDOOR_SCH_TYPE_MAYORS_RESIDENCE_MAIN_ENTRANCE,
    /* 18 */ ENDOOR_SCH_TYPE_18,
    /* 19 */ ENDOOR_SCH_TYPE_19,
    /* 20 */ ENDOOR_SCH_TYPE_20,
    /* 21 */ ENDOOR_SCH_TYPE_21, // unused
    /* 22 */ ENDOOR_SCH_TYPE_22,
    /* 23 */ ENDOOR_SCH_TYPE_23,
    /* 24 */ ENDOOR_SCH_TYPE_24,
    /* 25 */ ENDOOR_SCH_TYPE_25,
    /* 26 */ ENDOOR_SCH_TYPE_26,
    /* 27 */ ENDOOR_SCH_TYPE_27,
    /* 28 */ ENDOOR_SCH_TYPE_28,
    /* 29 */ ENDOOR_SCH_TYPE_MAGIC_HAGS_POTION_SHOP,
    /* 30 */ ENDOOR_SCH_TYPE_30, // unused
    /* 31 */ ENDOOR_SCH_TYPE_SWAMP_SHOOTING_GALLERY,
    /* 32 */ ENDOOR_SCH_TYPE_MAX
} EnDoorScheduleType;

#define ENDOOR_GET_TYPE(thisx) (((thisx)->params >> 7) & 7)
#define ENDOOR_GET_ACTION_VAR(thisx) (((thisx)->params) & 0x7F)

#define ENDOOR_GET_HALFDAYBIT_INDEX_FROM_ACTIONVAR_0_2_3(actionVar) ((actionVar) & 0x7)
#define ENDOOR_GET_TEXTOFFSET_FROM_ACTIONVAR_0_2_3(actionVar) (((actionVar) >> 3) & 0xF)

#define ENDOOR_PACK_ACTIONVAR_0_2_3(halfDayBitIndex, textOffset) ((((textOffset) & 0xF) << 3) | ((halfDayBitIndex) & 0x7))

#define ENDOOR_PARAMS(type, actionVar) ((((type) & 7) << 7) | ((actionVar) & 0x7F))

/**
 * `scheduleType` must be a value of the `EnDoorScheduleType` enum
 */
#define ENDOOR_PARAMS_SCHEDULE(scheduleType) ENDOOR_PARAMS(ENDOOR_TYPE_SCHEDULE, scheduleType)

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
