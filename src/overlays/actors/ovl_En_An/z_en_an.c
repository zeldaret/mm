/*
 * File: z_en_an.c
 * Overlay: ovl_En_An
 * Description: Anju
 */

#include "z_en_an.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#include "assets/objects/object_an2/object_an2.h"
#include "assets/objects/object_an3/object_an3.h"
#include "assets/objects/object_an4/object_an4.h"
#include "assets/objects/object_mask_kerfay/object_mask_kerfay.h"
#include "assets/objects/object_msmo/object_msmo.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAn*)thisx)

// Change this to non-zero to enable debug printing
#define DEBUG_PRINT 0

void EnAn_Init(Actor* thisx, PlayState* play);
void EnAn_Destroy(Actor* thisx, PlayState* play);
void EnAn_Update(Actor* thisx, PlayState* play);
void EnAn_Draw(Actor* thisx, PlayState* play);

// Action funcs
void EnAn_Initialize(EnAn* this, PlayState* play);
void EnAn_FollowSchedule(EnAn* this, PlayState* play);
void EnAn_Talk(EnAn* this, PlayState* play);

typedef enum AnjuScheduleResult {
    /*  0 */ ANJU_SCH_NONE,
    // Waiting for Kafei on the night of Day 3
    /*  1 */ ANJU_SCH_WAITING_FOR_KAFEI,
    // unused
    /*  2 */ ANJU_SCH_2,
    // Day 2, 13:45 ~ 15:25, No midnight meeting. Sit on the Laundry Pool under the rain
    /*  3 */ ANJU_SCH_LAUNDRY_POOL_SIT,
    // unused
    /*  4 */ ANJU_SCH_4,
    // unused
    /*  5 */ ANJU_SCH_5,
    // unused
    /*  6 */ ANJU_SCH_6,
    // unused
    /*  7 */ ANJU_SCH_7,
    // unused
    /*  8 */ ANJU_SCH_8,
    // unused
    /*  9 */ ANJU_SCH_9,
    // unused
    /* 10 */ ANJU_SCH_10,
    // unused
    /* 11 */ ANJU_SCH_11,
    // Day 3, Night, if not delivered the Pendant of Memories
    /* 12 */ ANJU_SCH_RANCH,
    // unused
    /* 13 */ ANJU_SCH_13,
    // Cooking lunch for Granny at 11:10 ~ 11:30 on Day 1 and Day 2 (if did had the Midnight meeting)
    /* 14 */ ANJU_SCH_COOKING,
    // unused
    /* 15 */ ANJU_SCH_15,
    // Day 1, 14:08 ~ 14:18. Receive Kafei's letter from Postman
    /* 16 */ ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN,
    // Day 1, 16:10 ~ 16:30. Attends the goron named after the player
    /* 17 */ ANJU_SCH_ATTEND_GORON,
    // Just standing on the front desk of the Inn
    /* 18 */ ANJU_SCH_RECEPTIONIST_IDLE,
    // Standing next to the Inn's front door at closing time
    /* 19 */ ANJU_SCH_WAITING_CLOSING_TIME,
    // unused
    /* 20 */ ANJU_SCH_20,
    // 12:00 ~ 12:15, Day 1 and Day 2 (if did had the Midnight meeting). Give lunch to Granny
    /* 21 */ ANJU_SCH_GIVE_LUNCH_TO_GRANNY,
    // Day 3, 06:00 ~ 11:00. Sweeping the Suite room. TODO: maybe rename to "cleaning Suite room"?
    /* 22 */ ANJU_SCH_SWEEPING,
    // Day 1, 00:00 ~ 06:00. Waiting for player at the kitchen to have the Midnight meeting.
    /* 23 */ ANJU_SCH_MIDNIGHT_MEETING,
    // Day 2, 21:30 ~ 23:00. On the staff room talking with her mom. This can be seen from the Knife Chamber
    /* 24 */ ANJU_SCH_TALKING_WITH_MOM,
    // Reunited with Kafei on the Staff room. Set manually in code instead of via script
    /* 25 */ ANJU_SCH_WITH_KAFEI,
    // Passing through to Granny's door (entering)
    /* 26 */ ANJU_SCH_DOOR_26,
    // Passing through to Granny's door (leaving)
    /* 27 */ ANJU_SCH_DOOR_27,
    // Passing through the door of the staff room (entering), after giving Granny's lunch
    /* 28 */ ANJU_SCH_DOOR_28,
    // Passing through the door of the staff room (leaving), after giving Granny's lunch
    /* 29 */ ANJU_SCH_DOOR_29,
    // Passing through the door of the staff room (entering), after closing the Inn
    /* 30 */ ANJU_SCH_DOOR_30,
    // Passing through the door of the staff room (leaving), to have the midnight meeting
    /* 31 */ ANJU_SCH_DOOR_31,
    // Passing through the door of the staff room (leaving), going to the Laundry Pool
    /* 32 */ ANJU_SCH_DOOR_32,
    // Passing through the Inn's front door (leaving) (inside the Inn), going to the Laundry Pool
    /* 33 */ ANJU_SCH_DOOR_33,
    // Passing through the Inn's front door (entering) (inside the Inn), going from the Laundry Pool
    /* 34 */ ANJU_SCH_DOOR_34,
    // Passing through the door of the staff room (entering), after going to the Laundry Pool
    /* 35 */ ANJU_SCH_DOOR_35,
    // Passing through the door of the Large Suite (leaving), after sweeping the floor
    /* 36 */ ANJU_SCH_DOOR_36,
    // Passing through the Inn's front door (leaving) (East Clock Town), going to the Laundry Pool
    /* 37 */ ANJU_SCH_DOOR_37,
    // Passing through the Inn's front door (entering) (East Clock Town), going from the Laundry Pool
    /* 38 */ ANJU_SCH_DOOR_38,
    // Passing through the door of the staff room (entering), after sweeping the floor
    /* 39 */ ANJU_SCH_DOOR_39,
    // Going from the front desk to the kitchen
    /* 40 */ ANJU_SCH_WALKING_40,
    // unused
    /* 41 */ ANJU_SCH_41,
    // Walking from the kitchen to Granny's room
    /* 42 */ ANJU_SCH_WALKING_42,
    // Inside Granny's room, walking to give her her food
    /* 43 */ ANJU_SCH_WALKING_43,
    // Inside Granny's room, walking out
    /* 44 */ ANJU_SCH_WALKING_44,
    // Left Granny's room, walking towards staff room
    /* 45 */ ANJU_SCH_WALKING_45,
    // Left staff room, walking to front desk
    /* 46 */ ANJU_SCH_WALKING_46,
    // Walking from the front desk to right next to the Inn's front door
    /* 47 */ ANJU_SCH_WALKING_47,
    // Walking from the Inn's front door after closing, to the staff room
    /* 48 */ ANJU_SCH_WALKING_48,
    // Walking from the staff room to the kitchen, to have the midnight meeting
    /* 49 */ ANJU_SCH_WALKING_49,
    // Walking from the staff room to Inn's front door, to go to the Laundry Pool
    /* 50 */ ANJU_SCH_WALKING_50,
    // Walking from the Inn's front door to the staff room, after going to the Laundry Pool
    /* 51 */ ANJU_SCH_WALKING_51,
    // Day 3, 11:00 ~ 11:25, Stopped sweeping, walking out of the room
    /* 52 */ ANJU_SCH_WALKING_52,
    // Day 3, 11:00 ~ 11:25, Walking through the hallway after sweeping
    /* 53 */ ANJU_SCH_WALKING_53,
    // Walking through East Clock Town, going to the Laundry Pool
    /* 54 */ ANJU_SCH_WALKING_54,
    // Walking through South Clock Town, East Clock Town perspective, going to the Laundry Pool
    /* 55 */ ANJU_SCH_WALKING_55,
    // Walking through Laundry Pool, entering
    /* 56 */ ANJU_SCH_WALKING_56,
    // Walking through Laundry Pool, leaving
    /* 57 */ ANJU_SCH_WALKING_57,
    // Walking through South Clock Town, East Clock Town perspective, going to the Inn from the Laundry Pool
    /* 58 */ ANJU_SCH_WALKING_58,
    // Walking through East Clock Town, going to the Inn from the Laundry Pool
    /* 59 */ ANJU_SCH_WALKING_59,
    // Walking through East Clock Town, South Clock Town perspective, going to the Laundry Pool
    /* 60 */ ANJU_SCH_WALKING_60,
    // Walking through South Clock Town, going to the Laundry Pool
    /* 61 */ ANJU_SCH_WALKING_61,
    // Walking through South Clock Town, going to the Inn from the Laundry Pool
    /* 62 */ ANJU_SCH_WALKING_62,
    // Walking through East Clock Town, South Clock Town perspective, going to the Inn from the Laundry Pool
    /* 63 */ ANJU_SCH_WALKING_63,
    /* 64 */ ANJU_SCH_MAX
} AnjuScheduleResult;

static u8 sScheduleScript[] = {
    /* 0x000 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(1, 0x151 - 0x005),
    /* 0x005 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x150 - 0x00A),
    /* 0x00A */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 10, 55, 0x14A - 0x011),
    /* 0x011 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(10, 55, 11, 10, 0x144 - 0x018),
    /* 0x018 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 10, 11, 30, 0x13E - 0x01F),
    /* 0x01F */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 30, 11, 50, 0x138 - 0x026),
    /* 0x026 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 50, 11, 55, 0x132 - 0x02D),
    /* 0x02D */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 55, 12, 0, 0x12C - 0x034),
    /* 0x034 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 0, 12, 15, 0x126 - 0x03B),
    /* 0x03B */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 15, 12, 20, 0x120 - 0x042),
    /* 0x042 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 20, 12, 25, 0x11A - 0x049),
    /* 0x049 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 25, 12, 55, 0x114 - 0x050),
    /* 0x050 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 55, 13, 0, 0x10E - 0x057),
    /* 0x057 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 15, 13, 20, 0x108 - 0x05E),
    /* 0x05E */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 20, 13, 50, 0x102 - 0x065),
    /* 0x065 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 50, 14, 8, 0x0FC - 0x06C),
    /* 0x06C */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(14, 8, 14, 18, 0x0F6 - 0x073),
    /* 0x073 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(14, 18, 16, 10, 0x0F0 - 0x079),
    /* 0x079 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 10, 16, 30, 0x0EA - 0x07F),
    /* 0x07F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 30, 19, 50, 0x0E4 - 0x085),
    /* 0x085 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x0DE - 0x08B),
    /* 0x08B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x0D8 - 0x091),
    /* 0x091 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 5, 0x0D2 - 0x097),
    /* 0x097 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 5, 21, 10, 0x0CC - 0x09D),
    /* 0x09D */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING, 0x0A2 - 0x0A1),
    /* 0x0A1 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0A2 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(23, 10, 23, 15, 0x0C6 - 0x0A8),
    /* 0x0A8 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(23, 15, 0, 0, 0x0C0 - 0x0AE),
    /* 0x0AE */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 6, 0, 0x0B5 - 0x0B4),
    /* 0x0B4 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0B5 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x0BF - 0x0B9),
    /* 0x0B9 */ SCHEDULE_CMD_RET_TIME(0, 0, 6, 0, ANJU_SCH_MIDNIGHT_MEETING),
    /* 0x0BF */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0C0 */ SCHEDULE_CMD_RET_TIME(23, 15, 0, 0, ANJU_SCH_WALKING_49),
    /* 0x0C6 */ SCHEDULE_CMD_RET_TIME(23, 10, 23, 15, ANJU_SCH_DOOR_31),
    /* 0x0CC */ SCHEDULE_CMD_RET_TIME(21, 5, 21, 10, ANJU_SCH_DOOR_30),
    /* 0x0D2 */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 5, ANJU_SCH_WALKING_48),
    /* 0x0D8 */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_WAITING_CLOSING_TIME),
    /* 0x0DE */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_WALKING_47),
    /* 0x0E4 */ SCHEDULE_CMD_RET_TIME(16, 30, 19, 50, ANJU_SCH_RECEPTIONIST_IDLE),
    /* 0x0EA */ SCHEDULE_CMD_RET_TIME(16, 10, 16, 30, ANJU_SCH_ATTEND_GORON),
    /* 0x0F0 */ SCHEDULE_CMD_RET_TIME(14, 18, 16, 10, ANJU_SCH_RECEPTIONIST_IDLE),
    /* 0x0F6 */ SCHEDULE_CMD_RET_TIME(14, 8, 14, 18, ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN),
    /* 0x0FC */ SCHEDULE_CMD_RET_TIME(13, 50, 14, 8, ANJU_SCH_RECEPTIONIST_IDLE),
    /* 0x102 */ SCHEDULE_CMD_RET_TIME(13, 20, 13, 50, ANJU_SCH_WALKING_46),
    /* 0x108 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 20, ANJU_SCH_DOOR_29),
    /* 0x10E */ SCHEDULE_CMD_RET_TIME(12, 55, 13, 0, ANJU_SCH_DOOR_28),
    /* 0x114 */ SCHEDULE_CMD_RET_TIME(12, 25, 12, 55, ANJU_SCH_WALKING_45),
    /* 0x11A */ SCHEDULE_CMD_RET_TIME(12, 20, 12, 25, ANJU_SCH_DOOR_27),
    /* 0x120 */ SCHEDULE_CMD_RET_TIME(12, 15, 12, 20, ANJU_SCH_WALKING_44),
    /* 0x126 */ SCHEDULE_CMD_RET_TIME(12, 0, 12, 15, ANJU_SCH_GIVE_LUNCH_TO_GRANNY),
    /* 0x12C */ SCHEDULE_CMD_RET_TIME(11, 55, 12, 0, ANJU_SCH_WALKING_43),
    /* 0x132 */ SCHEDULE_CMD_RET_TIME(11, 50, 11, 55, ANJU_SCH_DOOR_26),
    /* 0x138 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_WALKING_42),
    /* 0x13E */ SCHEDULE_CMD_RET_TIME(11, 10, 11, 30, ANJU_SCH_COOKING),
    /* 0x144 */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 10, ANJU_SCH_WALKING_40),
    /* 0x14A */ SCHEDULE_CMD_RET_TIME(6, 0, 10, 55, ANJU_SCH_RECEPTIONIST_IDLE),
    /* 0x150 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x151 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(2, 0x391 - 0x156),
    /* 0x156 */ SCHEDULE_CMD_CHECK_FLAG_L(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x29E - 0x15B),
    /* 0x15B */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x1F2 - 0x160),
    /* 0x160 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 3, 11, 9, 0x1EC - 0x167),
    /* 0x167 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 9, 11, 29, 0x1E6 - 0x16D),
    /* 0x16D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 29, 11, 39, 0x1E0 - 0x173),
    /* 0x173 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 24, 17, 30, 0x1DA - 0x179),
    /* 0x179 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 30, 17, 55, 0x1D4 - 0x17F),
    /* 0x17F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 55, 18, 0, 0x1CE - 0x185),
    /* 0x185 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 19, 50, 0x1C8 - 0x18B),
    /* 0x18B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x1C2 - 0x191),
    /* 0x191 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x1BC - 0x197),
    /* 0x197 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 0, 0x1B6 - 0x19D),
    /* 0x19D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 21, 5, 0x1B0 - 0x1A3),
    /* 0x1A3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 30, 23, 0, 0x1AA - 0x1A9),
    /* 0x1A9 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1AA */ SCHEDULE_CMD_RET_TIME(21, 30, 23, 0, ANJU_SCH_TALKING_WITH_MOM),
    /* 0x1B0 */ SCHEDULE_CMD_RET_TIME(21, 0, 21, 5, ANJU_SCH_DOOR_30),
    /* 0x1B6 */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 0, ANJU_SCH_WALKING_48),
    /* 0x1BC */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_WAITING_CLOSING_TIME),
    /* 0x1C2 */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_WALKING_47),
    /* 0x1C8 */ SCHEDULE_CMD_RET_TIME(18, 0, 19, 50, ANJU_SCH_RECEPTIONIST_IDLE),
    /* 0x1CE */ SCHEDULE_CMD_RET_TIME(17, 55, 18, 0, ANJU_SCH_DOOR_35),
    /* 0x1D4 */ SCHEDULE_CMD_RET_TIME(17, 30, 17, 55, ANJU_SCH_WALKING_51),
    /* 0x1DA */ SCHEDULE_CMD_RET_TIME(17, 24, 17, 30, ANJU_SCH_DOOR_34),
    /* 0x1E0 */ SCHEDULE_CMD_RET_TIME(11, 29, 11, 39, ANJU_SCH_DOOR_33),
    /* 0x1E6 */ SCHEDULE_CMD_RET_TIME(11, 9, 11, 29, ANJU_SCH_WALKING_50),
    /* 0x1EC */ SCHEDULE_CMD_RET_TIME(11, 3, 11, 9, ANJU_SCH_DOOR_32),
    /* 0x1F2 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_TOWN, 0x23F - 0x1F6),
    /* 0x1F6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 29, 11, 39, 0x239 - 0x1FC),
    /* 0x1FC */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 39, 12, 25, 0x233 - 0x202),
    /* 0x202 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 13, 15, 0x22D - 0x208),
    /* 0x208 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 55, 16, 45, 0x227 - 0x20E),
    /* 0x20E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 45, 17, 24, 0x221 - 0x214),
    /* 0x214 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 24, 17, 30, 0x21B - 0x21A),
    /* 0x21A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x21B */ SCHEDULE_CMD_RET_TIME(17, 24, 17, 30, ANJU_SCH_DOOR_38),
    /* 0x221 */ SCHEDULE_CMD_RET_TIME(16, 45, 17, 24, ANJU_SCH_WALKING_59),
    /* 0x227 */ SCHEDULE_CMD_RET_TIME(15, 55, 16, 45, ANJU_SCH_WALKING_58),
    /* 0x22D */ SCHEDULE_CMD_RET_TIME(12, 25, 13, 15, ANJU_SCH_WALKING_55),
    /* 0x233 */ SCHEDULE_CMD_RET_TIME(11, 39, 12, 25, ANJU_SCH_WALKING_54),
    /* 0x239 */ SCHEDULE_CMD_RET_TIME(11, 29, 11, 39, ANJU_SCH_DOOR_37),
    /* 0x23F */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_CLOCKTOWER, 0x274 - 0x243),
    /* 0x243 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 39, 12, 25, 0x26E - 0x249),
    /* 0x249 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 13, 15, 0x268 - 0x24F),
    /* 0x24F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 55, 16, 45, 0x262 - 0x255),
    /* 0x255 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 45, 17, 24, 0x25C - 0x25B),
    /* 0x25B */ SCHEDULE_CMD_RET_NONE(),
    /* 0x25C */ SCHEDULE_CMD_RET_TIME(16, 45, 17, 24, ANJU_SCH_WALKING_63),
    /* 0x262 */ SCHEDULE_CMD_RET_TIME(15, 55, 16, 45, ANJU_SCH_WALKING_62),
    /* 0x268 */ SCHEDULE_CMD_RET_TIME(12, 25, 13, 15, ANJU_SCH_WALKING_61),
    /* 0x26E */ SCHEDULE_CMD_RET_TIME(11, 39, 12, 25, ANJU_SCH_WALKING_60),
    /* 0x274 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_ALLEY, 0x29D - 0x278),
    /* 0x278 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 15, 13, 45, 0x297 - 0x27E),
    /* 0x27E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 45, 15, 25, 0x291 - 0x284),
    /* 0x284 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 25, 15, 55, 0x28B - 0x28A),
    /* 0x28A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x28B */ SCHEDULE_CMD_RET_TIME(15, 25, 15, 55, ANJU_SCH_WALKING_57),
    /* 0x291 */ SCHEDULE_CMD_RET_TIME(13, 45, 15, 25, ANJU_SCH_LAUNDRY_POOL_SIT),
    /* 0x297 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 45, ANJU_SCH_WALKING_56),
    /* 0x29D */ SCHEDULE_CMD_RET_NONE(),
    /* 0x29E */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x390 - 0x2A3),
    /* 0x2A3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 10, 55, 0x38A - 0x2AA),
    /* 0x2AA */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(10, 55, 11, 10, 0x384 - 0x2B1),
    /* 0x2B1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 10, 11, 30, 0x37E - 0x2B8),
    /* 0x2B8 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 30, 11, 50, 0x378 - 0x2BF),
    /* 0x2BF */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 50, 11, 55, 0x372 - 0x2C6),
    /* 0x2C6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 55, 12, 0, 0x36C - 0x2CD),
    /* 0x2CD */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 0, 12, 15, 0x366 - 0x2D4),
    /* 0x2D4 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 15, 12, 20, 0x360 - 0x2DB),
    /* 0x2DB */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 20, 12, 25, 0x35A - 0x2E1),
    /* 0x2E1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 12, 55, 0x354 - 0x2E7),
    /* 0x2E7 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 55, 13, 0, 0x34E - 0x2ED),
    /* 0x2ED */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 15, 13, 20, 0x348 - 0x2F3),
    /* 0x2F3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 20, 13, 50, 0x342 - 0x2F9),
    /* 0x2F9 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 50, 19, 50, 0x33C - 0x2FF),
    /* 0x2FF */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x336 - 0x305),
    /* 0x305 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x330 - 0x30B),
    /* 0x30B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 5, 0x32A - 0x311),
    /* 0x311 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 5, 21, 10, 0x324 - 0x317),
    /* 0x317 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 30, 23, 0, 0x31E - 0x31D),
    /* 0x31D */ SCHEDULE_CMD_RET_NONE(),
    /* 0x31E */ SCHEDULE_CMD_RET_TIME(21, 30, 23, 0, ANJU_SCH_TALKING_WITH_MOM),
    /* 0x324 */ SCHEDULE_CMD_RET_TIME(21, 5, 21, 10, ANJU_SCH_DOOR_30),
    /* 0x32A */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 5, ANJU_SCH_WALKING_48),
    /* 0x330 */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_WAITING_CLOSING_TIME),
    /* 0x336 */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_WALKING_47),
    /* 0x33C */ SCHEDULE_CMD_RET_TIME(13, 50, 19, 50, ANJU_SCH_RECEPTIONIST_IDLE),
    /* 0x342 */ SCHEDULE_CMD_RET_TIME(13, 20, 13, 50, ANJU_SCH_WALKING_46),
    /* 0x348 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 20, ANJU_SCH_DOOR_29),
    /* 0x34E */ SCHEDULE_CMD_RET_TIME(12, 55, 13, 0, ANJU_SCH_DOOR_28),
    /* 0x354 */ SCHEDULE_CMD_RET_TIME(12, 25, 12, 55, ANJU_SCH_WALKING_45),
    /* 0x35A */ SCHEDULE_CMD_RET_TIME(12, 20, 12, 25, ANJU_SCH_DOOR_27),
    /* 0x360 */ SCHEDULE_CMD_RET_TIME(12, 15, 12, 20, ANJU_SCH_WALKING_44),
    /* 0x366 */ SCHEDULE_CMD_RET_TIME(12, 0, 12, 15, ANJU_SCH_GIVE_LUNCH_TO_GRANNY),
    /* 0x36C */ SCHEDULE_CMD_RET_TIME(11, 55, 12, 0, ANJU_SCH_WALKING_43),
    /* 0x372 */ SCHEDULE_CMD_RET_TIME(11, 50, 11, 55, ANJU_SCH_DOOR_26),
    /* 0x378 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_WALKING_42),
    /* 0x37E */ SCHEDULE_CMD_RET_TIME(11, 10, 11, 30, ANJU_SCH_COOKING),
    /* 0x384 */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 10, ANJU_SCH_WALKING_40),
    /* 0x38A */ SCHEDULE_CMD_RET_TIME(6, 0, 10, 55, ANJU_SCH_RECEPTIONIST_IDLE),
    /* 0x390 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x391 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(3, 0x447 - 0x396),
    /* 0x396 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES, 0x3ED - 0x39A),
    /* 0x39A */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x3DB - 0x39E),
    /* 0x39E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 11, 0, 0x3D5 - 0x3A4),
    /* 0x3A4 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 0, 11, 25, 0x3CF - 0x3AA),
    /* 0x3AA */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 25, 11, 30, 0x3C9 - 0x3B0),
    /* 0x3B0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 30, 11, 50, 0x3C3 - 0x3B6),
    /* 0x3B6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 50, 12, 0, 0x3BD - 0x3BC),
    /* 0x3BC */ SCHEDULE_CMD_RET_NONE(),
    /* 0x3BD */ SCHEDULE_CMD_RET_TIME(11, 50, 12, 0, ANJU_SCH_DOOR_39),
    /* 0x3C3 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_WALKING_53),
    /* 0x3C9 */ SCHEDULE_CMD_RET_TIME(11, 25, 11, 30, ANJU_SCH_DOOR_36),
    /* 0x3CF */ SCHEDULE_CMD_RET_TIME(11, 0, 11, 25, ANJU_SCH_WALKING_52),
    /* 0x3D5 */ SCHEDULE_CMD_RET_TIME(6, 0, 11, 0, ANJU_SCH_SWEEPING),
    /* 0x3DB */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x3EC - 0x3DF),
    /* 0x3DF */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 6, 0, 0x3E6 - 0x3E5),
    /* 0x3E5 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x3E6 */ SCHEDULE_CMD_RET_TIME(18, 0, 6, 0, ANJU_SCH_RANCH),
    /* 0x3EC */ SCHEDULE_CMD_RET_NONE(),
    /* 0x3ED */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x446 - 0x3F1),
    /* 0x3F1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 11, 0, 0x440 - 0x3F7),
    /* 0x3F7 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 0, 11, 25, 0x43A - 0x3FD),
    /* 0x3FD */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 25, 11, 30, 0x434 - 0x403),
    /* 0x403 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 30, 11, 50, 0x42E - 0x409),
    /* 0x409 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 50, 12, 0, 0x428 - 0x40F),
    /* 0x40F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 5, 0, 0x422 - 0x415),
    /* 0x415 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(5, 0, 6, 0, 0x41C - 0x41B),
    /* 0x41B */ SCHEDULE_CMD_RET_NONE(),
    /* 0x41C */ SCHEDULE_CMD_RET_TIME(5, 0, 6, 0, ANJU_SCH_WAITING_FOR_KAFEI),
    /* 0x422 */ SCHEDULE_CMD_RET_TIME(18, 0, 5, 0, ANJU_SCH_WAITING_FOR_KAFEI),
    /* 0x428 */ SCHEDULE_CMD_RET_TIME(11, 50, 12, 0, ANJU_SCH_DOOR_39),
    /* 0x42E */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_WALKING_53),
    /* 0x434 */ SCHEDULE_CMD_RET_TIME(11, 25, 11, 30, ANJU_SCH_DOOR_36),
    /* 0x43A */ SCHEDULE_CMD_RET_TIME(11, 0, 11, 25, ANJU_SCH_WALKING_52),
    /* 0x440 */ SCHEDULE_CMD_RET_TIME(6, 0, 11, 0, ANJU_SCH_SWEEPING),
    /* 0x446 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x447 */ SCHEDULE_CMD_RET_NONE(),
};

/**
 * The schedule script is roughly equivalent to the following pseudo-code:

s32 scheduleScript(PlayState* play) {
    if (gSaveContext.save.day == 1) {
        if (play->sceneId == SCENE_YADOYA) {
            if ((6, 0) <= NOW <= (10, 55)) {
                return ANJU_SCH_RECEPTIONIST_IDLE;
            } else if ((10, 55) <= NOW <= (11, 10)) {
                return ANJU_SCH_WALKING_40;
            } else if ((11, 10) <= NOW <= (11, 30)) {
                return ANJU_SCH_COOKING;
            } else if ((11, 30) <= NOW <= (11, 50)) {
                return ANJU_SCH_WALKING_42;
            } else if ((11, 50) <= NOW <= (11, 55)) {
                return ANJU_SCH_DOOR_26;
            } else if ((11, 55) <= NOW <= (12, 0)) {
                return ANJU_SCH_WALKING_43;
            } else if ((12, 0) <= NOW <= (12, 15)) {
                return ANJU_SCH_GIVE_LUNCH_TO_GRANNY;
            } else if ((12, 15) <= NOW <= (12, 20)) {
                return ANJU_SCH_WALKING_44;
            } else if ((12, 20) <= NOW <= (12, 25)) {
                return ANJU_SCH_DOOR_27;
            } else if ((12, 25) <= NOW <= (12, 55)) {
                return ANJU_SCH_WALKING_45;
            } else if ((12, 55) <= NOW <= (13, 0)) {
                return ANJU_SCH_DOOR_28;
            } else if ((13, 15) <= NOW <= (13, 20)) {
                return ANJU_SCH_DOOR_29;
            } else if ((13, 20) <= NOW <= (13, 50)) {
                return ANJU_SCH_WALKING_46;
            } else if ((13, 50) <= NOW <= (14, 8)) {
                return ANJU_SCH_RECEPTIONIST_IDLE;
            } else if ((14, 8) <= NOW <= (14, 18)) {
                return ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN;
            } else if ((14, 18) <= NOW <= (16, 10)) {
                return ANJU_SCH_RECEPTIONIST_IDLE;
            } else if ((16, 10) <= NOW <= (16, 30)) {
                return ANJU_SCH_ATTEND_GORON;
            } else if ((16, 30) <= NOW <= (19, 50)) {
                return ANJU_SCH_RECEPTIONIST_IDLE;
            } else if ((19, 50) <= NOW <= (20, 20)) {
                return ANJU_SCH_WALKING_47;
            } else if ((20, 20) <= NOW <= (20, 30)) {
                return ANJU_SCH_WAITING_CLOSING_TIME;
            } else if ((20, 30) <= NOW <= (21, 5)) {
                return ANJU_SCH_WALKING_48;
            } else if ((21, 5) <= NOW <= (21, 10)) {
                return ANJU_SCH_DOOR_30;
            } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
                if ((23, 10) <= NOW <= (23, 15)) {
                    return ANJU_SCH_DOOR_31;
                } else if ((23, 15) <= NOW <= (0, 0)) {
                    return ANJU_SCH_WALKING_49;
                } else if ((0, 0) <= NOW <= (6, 0)) {
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_HAD_MIDNIGHT_MEETING)) {
                        return None;
                    }
                    return ANJU_SCH_MIDNIGHT_MEETING;
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
                if ((6, 0) <= NOW <= (10, 55)) {
                    return ANJU_SCH_RECEPTIONIST_IDLE;
                } else if ((10, 55) <= NOW <= (11, 10)) {
                    return ANJU_SCH_WALKING_40;
                } else if ((11, 10) <= NOW <= (11, 30)) {
                    return ANJU_SCH_COOKING;
                } else if ((11, 30) <= NOW <= (11, 50)) {
                    return ANJU_SCH_WALKING_42;
                } else if ((11, 50) <= NOW <= (11, 55)) {
                    return ANJU_SCH_DOOR_26;
                } else if ((11, 55) <= NOW <= (12, 0)) {
                    return ANJU_SCH_WALKING_43;
                } else if ((12, 0) <= NOW <= (12, 15)) {
                    return ANJU_SCH_GIVE_LUNCH_TO_GRANNY;
                } else if ((12, 15) <= NOW <= (12, 20)) {
                    return ANJU_SCH_WALKING_44;
                } else if ((12, 20) <= NOW <= (12, 25)) {
                    return ANJU_SCH_DOOR_27;
                } else if ((12, 25) <= NOW <= (12, 55)) {
                    return ANJU_SCH_WALKING_45;
                } else if ((12, 55) <= NOW <= (13, 0)) {
                    return ANJU_SCH_DOOR_28;
                } else if ((13, 15) <= NOW <= (13, 20)) {
                    return ANJU_SCH_DOOR_29;
                } else if ((13, 20) <= NOW <= (13, 50)) {
                    return ANJU_SCH_WALKING_46;
                } else if ((13, 50) <= NOW <= (19, 50)) {
                    return ANJU_SCH_RECEPTIONIST_IDLE;
                } else if ((19, 50) <= NOW <= (20, 20)) {
                    return ANJU_SCH_WALKING_47;
                } else if ((20, 20) <= NOW <= (20, 30)) {
                    return ANJU_SCH_WAITING_CLOSING_TIME;
                } else if ((20, 30) <= NOW <= (21, 5)) {
                    return ANJU_SCH_WALKING_48;
                } else if ((21, 5) <= NOW <= (21, 10)) {
                    return ANJU_SCH_DOOR_30;
                } else if ((21, 30) <= NOW <= (23, 0)) {
                    return ANJU_SCH_TALKING_WITH_MOM;
                } else {
                    return None;
                }
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_YADOYA) {
            if ((11, 3) <= NOW <= (11, 9)) {
                return ANJU_SCH_DOOR_32;
            } else if ((11, 9) <= NOW <= (11, 29)) {
                return ANJU_SCH_WALKING_50;
            } else if ((11, 29) <= NOW <= (11, 39)) {
                return ANJU_SCH_DOOR_33;
            } else if ((17, 24) <= NOW <= (17, 30)) {
                return ANJU_SCH_DOOR_34;
            } else if ((17, 30) <= NOW <= (17, 55)) {
                return ANJU_SCH_WALKING_51;
            } else if ((17, 55) <= NOW <= (18, 0)) {
                return ANJU_SCH_DOOR_35;
            } else if ((18, 0) <= NOW <= (19, 50)) {
                return ANJU_SCH_RECEPTIONIST_IDLE;
            } else if ((19, 50) <= NOW <= (20, 20)) {
                return ANJU_SCH_WALKING_47;
            } else if ((20, 20) <= NOW <= (20, 30)) {
                return ANJU_SCH_WAITING_CLOSING_TIME;
            } else if ((20, 30) <= NOW <= (21, 0)) {
                return ANJU_SCH_WALKING_48;
            } else if ((21, 0) <= NOW <= (21, 5)) {
                return ANJU_SCH_DOOR_30;
            } else if ((21, 30) <= NOW <= (23, 0)) {
                return ANJU_SCH_TALKING_WITH_MOM;
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_TOWN) {
            if ((11, 29) <= NOW <= (11, 39)) {
                return ANJU_SCH_DOOR_37;
            } else if ((11, 39) <= NOW <= (12, 25)) {
                return ANJU_SCH_WALKING_54;
            } else if ((12, 25) <= NOW <= (13, 15)) {
                return ANJU_SCH_WALKING_55;
            } else if ((15, 55) <= NOW <= (16, 45)) {
                return ANJU_SCH_WALKING_58;
            } else if ((16, 45) <= NOW <= (17, 24)) {
                return ANJU_SCH_WALKING_59;
            } else if ((17, 24) <= NOW <= (17, 30)) {
                return ANJU_SCH_DOOR_38;
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_CLOCKTOWER) {
            if ((11, 39) <= NOW <= (12, 25)) {
                return ANJU_SCH_WALKING_60;
            } else if ((12, 25) <= NOW <= (13, 15)) {
                return ANJU_SCH_WALKING_61;
            } else if ((15, 55) <= NOW <= (16, 45)) {
                return ANJU_SCH_WALKING_62;
            } else if ((16, 45) <= NOW <= (17, 24)) {
                return ANJU_SCH_WALKING_63;
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_ALLEY) {
            if ((13, 15) <= NOW <= (13, 45)) {
                return ANJU_SCH_WALKING_56;
            } else if ((13, 45) <= NOW <= (15, 25)) {
                return ANJU_SCH_LAUNDRY_POOL_SIT;
            } else if ((15, 25) <= NOW <= (15, 55)) {
                return ANJU_SCH_WALKING_57;
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
                    return ANJU_SCH_SWEEPING;
                } else if ((11, 0) <= NOW <= (11, 25)) {
                    return ANJU_SCH_WALKING_52;
                } else if ((11, 25) <= NOW <= (11, 30)) {
                    return ANJU_SCH_DOOR_36;
                } else if ((11, 30) <= NOW <= (11, 50)) {
                    return ANJU_SCH_WALKING_53;
                } else if ((11, 50) <= NOW <= (12, 0)) {
                    return ANJU_SCH_DOOR_39;
                } else if ((18, 0) <= NOW <= (5, 0)) {
                    return ANJU_SCH_WAITING_FOR_KAFEI;
                } else if ((5, 0) <= NOW <= (6, 0)) {
                    return ANJU_SCH_WAITING_FOR_KAFEI;
                } else {
                    return None;
                }
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_YADOYA) {
            if ((6, 0) <= NOW <= (11, 0)) {
                return ANJU_SCH_SWEEPING;
            } else if ((11, 0) <= NOW <= (11, 25)) {
                return ANJU_SCH_WALKING_52;
            } else if ((11, 25) <= NOW <= (11, 30)) {
                return ANJU_SCH_DOOR_36;
            } else if ((11, 30) <= NOW <= (11, 50)) {
                return ANJU_SCH_WALKING_53;
            } else if ((11, 50) <= NOW <= (12, 0)) {
                return ANJU_SCH_DOOR_39;
            } else {
                return None;
            }
        } else if (play->sceneId == SCENE_OMOYA) {
            if ((18, 0) <= NOW <= (6, 0)) {
                return ANJU_SCH_RANCH;
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
 */

static s32 sSearchTimePathLimit[ANJU_SCH_MAX] = {
    -1, // ANJU_SCH_NONE
    10, // ANJU_SCH_WAITING_FOR_KAFEI
    -1, // ANJU_SCH_2
    0,  // ANJU_SCH_LAUNDRY_POOL_SIT
    -1, // ANJU_SCH_4
    -1, // ANJU_SCH_5
    -1, // ANJU_SCH_6
    -1, // ANJU_SCH_7
    -1, // ANJU_SCH_8
    -1, // ANJU_SCH_9
    -1, // ANJU_SCH_10
    -1, // ANJU_SCH_11
    -1, // ANJU_SCH_RANCH
    -1, // ANJU_SCH_13
    0,  // ANJU_SCH_COOKING
    -1, // ANJU_SCH_15
    10, // ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN
    10, // ANJU_SCH_ATTEND_GORON
    10, // ANJU_SCH_RECEPTIONIST_IDLE
    11, // ANJU_SCH_WAITING_CLOSING_TIME
    -1, // ANJU_SCH_20
    4,  // ANJU_SCH_GIVE_LUNCH_TO_GRANNY
    22, // ANJU_SCH_SWEEPING
    15, // ANJU_SCH_MIDNIGHT_MEETING
    -1, // ANJU_SCH_TALKING_WITH_MOM
    -1, // ANJU_SCH_WITH_KAFEI
    3,  // ANJU_SCH_DOOR_26
    6,  // ANJU_SCH_DOOR_27
    8,  // ANJU_SCH_DOOR_28
    9,  // ANJU_SCH_DOOR_29
    13, // ANJU_SCH_DOOR_30
    14, // ANJU_SCH_DOOR_31
    16, // ANJU_SCH_DOOR_32
    18, // ANJU_SCH_DOOR_33
    19, // ANJU_SCH_DOOR_34
    21, // ANJU_SCH_DOOR_35
    23, // ANJU_SCH_DOOR_36
    0,  // ANJU_SCH_DOOR_37
    5,  // ANJU_SCH_DOOR_38
    25, // ANJU_SCH_DOOR_39
    0,  // ANJU_SCH_WALKING_40
    1,  // ANJU_SCH_41
    2,  // ANJU_SCH_WALKING_42
    4,  // ANJU_SCH_WALKING_43
    5,  // ANJU_SCH_WALKING_44
    7,  // ANJU_SCH_WALKING_45
    10, // ANJU_SCH_WALKING_46
    11, // ANJU_SCH_WALKING_47
    12, // ANJU_SCH_WALKING_48
    15, // ANJU_SCH_WALKING_49
    17, // ANJU_SCH_WALKING_50
    20, // ANJU_SCH_WALKING_51
    22, // ANJU_SCH_WALKING_52
    24, // ANJU_SCH_WALKING_53
    1,  // ANJU_SCH_WALKING_54
    2,  // ANJU_SCH_WALKING_55
    0,  // ANJU_SCH_WALKING_56
    1,  // ANJU_SCH_WALKING_57
    3,  // ANJU_SCH_WALKING_58
    4,  // ANJU_SCH_WALKING_59
    0,  // ANJU_SCH_WALKING_60
    1,  // ANJU_SCH_WALKING_61
    2,  // ANJU_SCH_WALKING_62
    3,  // ANJU_SCH_WALKING_63
};

s32 sAnjuMsgScript_SchReceiveLetterFromPostman[0x1B] = {
    0x00560800, 0x44090000, 0x0E28BA0C, 0x09000017, 0x0E28BB0C, 0x09000018, 0x0E28BC0C, 0x09000017, 0x0E28BD0C,
    0x09000018, 0x0E28BE0C, 0x09000017, 0x0E28BF0C, 0x09000018, 0x0E28C02D, 0x00012D00, 0x0B0C0900, 0x00115608,
    0x10090000, 0x0E295C0C, 0x09000017, 0x0E295D0C, 0x09000018, 0x0E295E2D, 0x00012D00, 0x0B0C0900, 0x00100000,
};

s32 sAnjuMsgScript_SchAttendGoron[0x21] = {
    0x09000000, 0x4B10001E, 0x0E28B10C, 0x09000017, 0x0E28B20C, 0x09000018, 0x0E28B32D, 0x00011137, 0x020C0900,
    0x00100056, 0x10002E0E, 0x28B10C09, 0x0000170E, 0x28B50C09, 0x0000180E, 0x28B60C09, 0x0000170E, 0x28B70C09,
    0x0000180E, 0x28B82D00, 0x010C0900, 0x00115610, 0x10090000, 0x170E2956, 0x0C090000, 0x180E2957, 0x0C090000,
    0x170E2958, 0x0C090000, 0x180E2959, 0x2D00010C, 0x09000012, 0x10000000,
};

s32 sAnjuMsgScript_SchGiveLunchToGranny[0x15] = {
    0x09000017, 0x0E28C70C, 0x09000018, 0x0E28C80C, 0x09000017, 0x0E28C90C, 0x09000018,
    0x0E28CA0C, 0x09000017, 0x0E28CB0C, 0x09000018, 0x0E28CC0C, 0x09000017, 0x0E28CD0C,
    0x09000018, 0x0E28CE0C, 0x09000017, 0x0E28CF2D, 0x12D00,    0x0E0C0900, 0x100000,
};

s32 sAnjuMsgScript_80B5885C[0x37] = {
    0x220B0000, 0x69002020, 0x64004B,   0x1000B700, 0x370100AA, 0x370200,   0x550E28A0, 0x0C090000,
    0x0F28A80C, 0x05000000, 0x30000030, 0x0E28A90C, 0x0F28AA0C, 0x0F28AB0C, 0x120600A0, 0x1300,
    0xA02F0000, 0x2E2D0014, 0x0C114B10, 0x0700000E, 0x28AD2D00, 0x010C2400, 0x41161031, 0x0E28A30C,
    0x0900000F, 0x28A52D00, 0x010C1137, 0x01100020, 0x2000340E, 0x28A00C09, 0xF28,      0xA10C0500,
    0xF00,      0x300E28,   0xA20C0900, 0xF28A3,    0x0C190008, 0x310E28A4, 0x0C090000, 0x0F28A52D,
    0x10C11,    0x20201023, 0x400012,   0x0E28A00C, 0x0900000F, 0x28A62D00, 0x010C2400, 0x40100E28,
    0xA72D0001, 0x0C102300, 0x41000B0E, 0x28AC2D00, 0x010C2400, 0x41100E28, 0xAD0C1000,
};

s32 sAnjuMsgScript_InnCloseTime[3] = { 0x0E18852D, 0x10C12, 0x10000000 };

s32 sAnjuMsgScript_80B58944[2] = { 0x0E28AF2D, 0x10C10 };

s32 sAnjuMsgScript_80B5894C[2] = { 0x0E28C12D, 0x10C10 };

s32 sAnjuMsgScript_SchCooking[0xB] = {
    0x350100,   0x1C0E28C3, 0x0C0F28C4, 0x0C150900, 0xE28C5,    0x2D00010C,
    0x15090000, 0x11350112, 0x100E28C2, 0x2D00010C, 0x10000000,
};

s32 sAnjuMsgScript_80B58980[2] = { 0x0E28C62D, 0x10C10 };

s32 sAnjuMsgScript_SchSweeping[3] = { 0x0E28F70C, 0x0F28F82D, 0x10C10 };

s32 sAnjuMsgScript_80B58994[2] = { 0x0E28F82D, 0x10C10 };

s32 sAnjuMsgScript_SchRanch[4] = { 0x0E28F90C, 0x0F28FA0C, 0x0F28FB2D, 0x10C10 };

s32 sAnjuMsgScript_SchMidnightMeeting[0x14] = {
    0x0E28D70C, 0x0F28D80C, 0x0F28D90C, 0x0F28DA0C, 0x0F28DB0C, 0x05000700, 0x731,
    0x0E28D919, -0x16CFF2,  0x28DC0C11, 0x32201132, 0x10120600, 0xAA000013, 0xAA2F00,
    0x2E2D00,   0x012D0017, 0x2D00160C, 0x0700000E, 0x28DE0C15, 0x09000010,
};

// Surprised: "nevermind"
s32 sAnjuMsgScript_80B589FC[2] = { 0x0E28D62D, 0x10C10 };

s32 sAnjuMsgScript_DekuDefault[8] = {
    0x522000, 0x100E294F, 0x0C0F2950, 0x2D00010C, 0x12115220, 0x100E2951, 0x2D00010C, 0x12100000,
};

s32 sAnjuMsgScript_SchLaundryPoolDeku[6] = { 0x524000, 0x0B0E2952, 0x2D00010C, 0x11524010, 0x0E29532D, 0x10C10 };

s32 sAnjuMsgScript_80B58A3C[2] = { 0x0E28E02D, 0x10C10 };

s32 sAnjuMsgScript_80B58A44[0x1E] = {
    0x320800,   0x080E28D5, 0x2D00010C, 0x10003220,  0x80E28,    -0x2BD2FFFF, 0x0C100033, 0x01001A25,
    0x30001D,   0x27000300, 0x080E28E3, 0x2D00010C,  0x100E28E2, 0x2D00010C,  0x100E28E1, 0x2D00010C,
    0x100E28E4, 0x0C0E00FF, 0x1E003600, 0x0E000000,  0x0C2C28E7, 0x0C2F0000,  0x2D00010C, 0x1012102C,
    0x28E50C2F, 0xC2A,      0x300F28,   -0x19D2FFFF, 0x2D001A0C, 0x11330110,
};

s32 sAnjuMsgScript_80B58ABC[2] = { 0x0E28D02D, 0x10C10 };

s32 sAnjuMsgScript_80B58AC4[9] = {
    0x320800, 0x160E28D1, 0x0C0F28D2, 0x0C0F28D3, 0x2D00152D, 0x10C11, 0x3208100E, 0x28D32D00, 0x010C1000,
};

s32 sAnjuMsgScript_SchWaitingForKafei[3] = { 0x0E28DF2D, 0x10C12, 0x10000000 };

s32 sAnjuMsgScript_SchLaundryPoolDefault[0x12] = {
    0x372000,    0x29003208, 0x2A0E28,   -0x17F3EAF7, 0xE28,      -0x16F3F0D8, -0x15F3EAF7, 0xE28,   -0x14F3F0D8,
    -0x13D2FFFF, 0x0C121137, 0x20100E28, -0x13F3EDF0, 0x0E28EE0C, 0x0F28EB0C,  0x0F28EC2D,  0x10C12, 0x11372010,
};

s32 sAnjuMsgScript_SchLaundryPoolKafeiMask[0x10] = {
    0x372000,   0x21003208, 0x220E28,    -0x17F3F0D8, -0x12F3EAF7, 0xE28,      -0x14F3F0D8, -0x13D2FFFF,
    0x0C121137, 0x20100E28, -0x13F3EDF0, 0x0E28EE0C,  0x0F28EB0C,  0x0F28EC2D, 0x10C12,     0x11372010,
};

// Anju says the Inn is full and tell the player to tell that to his mother
s32 sAnjuMsgScript_80B58B7C[3] = { 0x0E29512D, 0x10C12, 0x10000000 };

// Tells player that they should talk in the kitchen instead
s32 sAnjuMsgScript_80B58B88[2] = { 0x0E29612D, 0x10C10 };

s32 sAnjuMsgScript_SchWithKafei[3] = { 0x0E291B2D, 0x10C12, 0x10000000 };

ActorInit En_An_InitVars = {
    ACTOR_EN_AN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(EnAn),
    (ActorFunc)EnAn_Init,
    (ActorFunc)EnAn_Destroy,
    (ActorFunc)EnAn_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 14, 62, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

s32 EnAn_InitializeObjectSlots(EnAn* this, PlayState* play) {
    s32 ret = false;

    if ((this->roomNum != play->roomCtx.curRoom.num) && (play->roomCtx.status == 0) && !this->slotsInitialized) {
        this->msmoObjectSlot = SubS_GetObjectSlot(OBJECT_MSMO, play);
        this->an4ObjectSlot = SubS_GetObjectSlot(OBJECT_AN4, play);
        this->maskKerfayObjectSlot = SubS_GetObjectSlot(OBJECT_MASK_KERFAY, play);
        this->an3ObjectSlot = SubS_GetObjectSlot(OBJECT_AN3, play);
        this->an2ObjectSlot = SubS_GetObjectSlot(OBJECT_AN2, play);
        this->actor.draw = NULL;
        this->roomNum = play->roomCtx.curRoom.num;
        this->slotsInitialized = true;
    }

    if (!this->slotsInitialized) {
        return false;
    }

    if (((this->an2ObjectSlot > OBJECT_SLOT_NONE) && !SubS_IsObjectLoaded(this->an2ObjectSlot, play)) ||
        ((this->an3ObjectSlot > OBJECT_SLOT_NONE) && !SubS_IsObjectLoaded(this->an3ObjectSlot, play)) ||
        ((this->maskKerfayObjectSlot > OBJECT_SLOT_NONE) && !SubS_IsObjectLoaded(this->maskKerfayObjectSlot, play)) ||
        ((this->an4ObjectSlot > OBJECT_SLOT_NONE) && !SubS_IsObjectLoaded(this->an4ObjectSlot, play)) ||
        ((this->msmoObjectSlot > OBJECT_SLOT_NONE) && !SubS_IsObjectLoaded(this->msmoObjectSlot, play))) {
        ret = true;
    } else {
        this->actor.draw = EnAn_Draw;
        this->slotsInitialized = false;
    }

    return ret;
}

Actor* EnAn_FindActor(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAn*)foundActor) && (foundActor->update != NULL)) {
            break;
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }

        foundActor = foundActor->next;
    }

    return foundActor;
}

Actor* func_80B53A7C(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAn*)foundActor) && (foundActor->update != NULL)) {
            if (!(foundActor->params & ENAN_8000)) {
                break;
            }
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }

        foundActor = foundActor->next;
    }

    return foundActor;
}

EnDoor* EnAn_FindDoor(PlayState* play, AnjuScheduleResult scheduleOutputResult) {
    s32 switchFlag;

    switch (scheduleOutputResult) {
        case ANJU_SCH_DOOR_26:
        case ANJU_SCH_DOOR_27:
            switchFlag = 0xD;
            break;

        case ANJU_SCH_DOOR_33:
        case ANJU_SCH_DOOR_34:
        case ANJU_SCH_DOOR_37:
        case ANJU_SCH_DOOR_38:
            switchFlag = 0xB;
            break;

        case ANJU_SCH_DOOR_36:
            switchFlag = 0x10;
            break;

        case ANJU_SCH_DOOR_28:
        case ANJU_SCH_DOOR_29:
        case ANJU_SCH_DOOR_30:
        case ANJU_SCH_DOOR_31:
        case ANJU_SCH_DOOR_32:
        case ANJU_SCH_DOOR_35:
        case ANJU_SCH_DOOR_39:
            switchFlag = 0xE;
            break;

        default:
            return NULL;
    }

    return SubS_FindDoor(play, switchFlag);
}

/**
 * Anju stores her animations across 4 objects and all of them are put together right next to each other in the
 * sAnimationInfo array. Due to this, animation functions check which object to load by comparing index ranges. To make
 * this a bit easier to read, this enum includes `ENAN_ANIMOBJ_*` values that mark when a range of animations of a
 * certain object start
 */
typedef enum EnAnAnimation {
    /* -1 */ ENAN_ANIM_NONE = -1,
    /*  0 */ ENAN_ANIM_HOLDING_HANDS,
    /*  1 */ ENAN_ANIM_IDLE,
    /*  2 */ ENAN_ANIM_IDLE_MORPH,
    /*  3 */ ENAN_ANIM_BOWING,
    /*  4 */ ENAN_ANIM_BOWING_MORPH,
    /*  5 */ ENAN_ANIM_SURPRISED,
    /*  6 */ ENAN_ANIM_LOOKING_UP_RELIEVED,
    /*  7 */ ENAN_ANIM_WALK,
    /*  8 */ ENAN_ANIM_WALK2, // Duplicate of ENAN_ANIM_WALK
    /*  9 */ ENAN_ANIM_SIT,
    /* 10 */ ENAN_ANIM_SIT_MORPH,
    /* 11 */ ENAN_ANIM_SITTING_IN_DISBELIEVE,
    /* 12 */ ENAN_ANIM_COOKING,
    /* 13 */ ENAN_ANIM_TASTING,
    /* 14 */ ENAN_ANIM_TASTING_END,
    /* 15 */ ENAN_ANIM_WAITING_WITH_TRAY,
    /* 16 */ ENAN_ANIM_WALKING_WITH_TRAY,

    /* 17 */ ENAN_ANIMOBJ_AN2,
    /* 17 */ ENAN_ANIM_UMBRELLA_IDLE = ENAN_ANIMOBJ_AN2,
    /* 18 */ ENAN_ANIM_UMBRELLA_WALK,
    /* 19 */ ENAN_ANIM_UMBRELLA_SIT,
    /* 20 */ ENAN_ANIM_UMBRELLA_CRYING,

    /* 21 */ ENAN_ANIMOBJ_AN3,
    /* 21 */ ENAN_ANIM_BROOM_IDLE = ENAN_ANIMOBJ_AN3,
    /* 22 */ ENAN_ANIM_BROOM_WALK,
    /* 23 */ ENAN_ANIM_BROOM_SWEEP,
    /* 24 */ ENAN_ANIM_24, //! @bug See note at `sAnimationInfo`

    /* 25 */ ENAN_ANIMOBJ_AN4,
    /* 25 */ ENAN_ANIM_25 = ENAN_ANIMOBJ_AN4,
    /* 26 */ ENAN_ANIM_26,
    /* 27 */ ENAN_ANIM_27,
    /* 28 */ ENAN_ANIM_28,
    /* 29 */ ENAN_ANIM_29,
    /* 30 */ ENAN_ANIM_30,
    /* 31 */ ENAN_ANIM_31,
    /* 32 */ ENAN_ANIM_32,
    /* 33 */ ENAN_ANIM_33,
    /* 34 */ ENAN_ANIM_SITTING_RAISE_FACE,
    /* 35 */ ENAN_ANIM_35,
    /* 36 */ ENAN_ANIM_MAX
} EnAnAnimation;

static AnimationInfoS sAnimationInfo[ENAN_ANIM_MAX] = {
    { &gAnju1HoldingHandsAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },        // ENAN_ANIM_HOLDING_HANDS
    { &gAnju1IdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },                // ENAN_ANIM_IDLE
    { &gAnju1IdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },               // ENAN_ANIM_IDLE_MORPH
    { &gAnju1BowingAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },              // ENAN_ANIM_BOWING
    { &gAnju1BowingAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -6 },             // ENAN_ANIM_BOWING_MORPH
    { &gAnju1SurprisedAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },           // ENAN_ANIM_SURPRISED
    { &gAnju1LookingUpRelievedAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },   // ENAN_ANIM_LOOKING_UP_RELIEVED
    { &gAnju1WalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },                // ENAN_ANIM_WALK
    { &gAnju1WalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },                // ENAN_ANIM_WALK2
    { &gAnju1SitAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },                 // ENAN_ANIM_SIT
    { &gAnju1SitAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },                // ENAN_ANIM_SIT_MORPH
    { &gAnju1SittingInDisbelieveAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_SITTING_IN_DISBELIEVE
    { &gAnju1CookingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },             // ENAN_ANIM_COOKING
    { &gAnju1TastingAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },             // ENAN_ANIM_TASTING
    { &gAnju1TastingEndAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },          // ENAN_ANIM_TASTING_END
    { &gAnju1WaitingWithTrayAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // ENAN_ANIM_WAITING_WITH_TRAY
    { &gAnju1WalkingWithTrayAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // ENAN_ANIM_WALKING_WITH_TRAY

    // ENAN_ANIMOBJ_AN2
    { &gAnju2UmbrellaIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },   // ENAN_ANIM_UMBRELLA_IDLE
    { &gAnju2UmbrellaWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },   // ENAN_ANIM_UMBRELLA_WALK
    { &gAnju2UmbrellaSitAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },    // ENAN_ANIM_UMBRELLA_SIT
    { &gAnju2UmbrellaCryingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_UMBRELLA_CRYING

    // ENAN_ANIMOBJ_AN3
    { &gAnju3BroomIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_BROOM_IDLE
    { &gAnju3BroomWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_BROOM_WALK
    { &gAnju3BroomSweepAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_BROOM_SWEEP
    //! @bug Uses symbol from OBJECT_AN2 instead of OBJECT_AN3
    { &gAnju2UmbrellaSitAnim, -1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_24

    // ENAN_ANIMOBJ_AN4
    { &object_an4_Anim_006CC0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // ENAN_ANIM_25
    { &object_an4_Anim_007E3C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },     // ENAN_ANIM_26
    { &object_an4_Anim_0088C0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // ENAN_ANIM_27
    { &object_an4_Anim_0013C8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },     // ENAN_ANIM_28
    { &object_an4_Anim_002550, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // ENAN_ANIM_29
    { &object_an4_Anim_00353C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },     // ENAN_ANIM_30
    { &object_an4_Anim_004498, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // ENAN_ANIM_31
    { &object_an4_Anim_0060B4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },     // ENAN_ANIM_32
    { &object_an4_Anim_00041C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },     // ENAN_ANIM_33
    { &gAnju4SittingRaiseFaceAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_SITTING_RAISE_FACE
    { &object_an4_Anim_00506C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // ENAN_ANIM_35
};

s32 EnAn_UpdateSkel(EnAn* this, PlayState* play) {
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot = OBJECT_SLOT_NONE;
    s32 ret = 0;

    if ((this->animIndex >= ENAN_ANIMOBJ_AN4) && (this->an4ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an4ObjectSlot;
    } else if ((this->animIndex >= ENAN_ANIMOBJ_AN3) && (this->an3ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an3ObjectSlot;
    } else if ((this->animIndex >= ENAN_ANIMOBJ_AN2) && (this->an2ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an2ObjectSlot;
    } else if (this->animIndex < ENAN_ANIMOBJ_AN2) {
        otherObjectSlot = originalObjectSlot;
    }

    if (otherObjectSlot <= OBJECT_SLOT_NONE) {
        return 0;
    }

    if (otherObjectSlot > OBJECT_SLOT_NONE) {
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[otherObjectSlot].segment);
        this->skelAnime.playSpeed = this->unk_368;
        ret = SkelAnime_Update(&this->skelAnime);
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[originalObjectSlot].segment);
    }

    return ret;
}

s32 EnAn_ChangeAnim(EnAn* this, PlayState* play, EnAnAnimation animIndex) {
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot = OBJECT_SLOT_NONE;
    s32 changeAnim = false;
    s32 ret = false;

    if ((animIndex >= ENAN_ANIMOBJ_AN4) && (this->an4ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an4ObjectSlot;
    } else if ((animIndex >= ENAN_ANIMOBJ_AN3) && (this->an3ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an3ObjectSlot;
    } else if ((animIndex >= ENAN_ANIMOBJ_AN2) && (this->an2ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an2ObjectSlot;
    } else if (animIndex < ENAN_ANIMOBJ_AN2) {
        otherObjectSlot = originalObjectSlot;
    }

    if (otherObjectSlot <= OBJECT_SLOT_NONE) {
        return 0;
    }

    switch (animIndex) {
        case ENAN_ANIM_IDLE:
        case ENAN_ANIM_IDLE_MORPH:
            if ((this->animIndex != ENAN_ANIM_IDLE) && (this->animIndex != ENAN_ANIM_IDLE_MORPH)) {
                changeAnim = true;
            }
            break;

        case ENAN_ANIM_WALK:
        case ENAN_ANIM_WALK2:
            if ((this->animIndex != ENAN_ANIM_WALK) && (this->animIndex != ENAN_ANIM_WALK2)) {
                changeAnim = true;
            }
            break;

        case ENAN_ANIM_SIT:
        case ENAN_ANIM_SIT_MORPH:
            if ((this->animIndex != ENAN_ANIM_SIT) && (this->animIndex != ENAN_ANIM_SIT_MORPH)) {
                changeAnim = true;
            }
            break;

        default:
            if (animIndex != this->animIndex) {
                changeAnim = true;
            }
            break;
    }

    if (changeAnim && (otherObjectSlot > OBJECT_SLOT_NONE)) {
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[otherObjectSlot].segment);
        this->animIndex = animIndex;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        this->unk_368 = this->skelAnime.playSpeed;
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[originalObjectSlot].segment);
    }

    return ret;
}

void EnAn_UpdateCollider(EnAn* this, PlayState* play) {
    f32 temp;
    s32 pad;
    Vec3f sp24;

    if (this->scheduleResult == ANJU_SCH_WITH_KAFEI) {
        static Vec3f D_80B58E34 = { 0.0f, 0.0f, 8.0f };

        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80B58E34, &sp24);
        this->collider.dim.radius = 20;
        Math_Vec3f_ToVec3s(&this->collider.dim.pos, &sp24);
    } else {
        Collider_UpdateCylinder(&this->actor, &this->collider);
    }

    temp = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = TRUNCF_BINANG(temp);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

typedef enum EnAnEyes {
    /* 0 */ ENAN_EYES_OPEN,
    /* 1 */ ENAN_EYES_HALF1,
    /* 2 */ ENAN_EYES_CLOSED,
    /* 3 */ ENAN_EYES_HALF2,
    /* 4 */ ENAN_EYES_4,
    /* 5 */ ENAN_EYES_SAD,
    /* 6 */ ENAN_EYES_ANGRY,
    /* 7 */ ENAN_EYES_MAX
} EnAnEyes;

typedef enum EnAnMouth {
    /* 0 */ ENAN_MOUTH_0,
    /* 1 */ ENAN_MOUTH_HAPPY,
    /* 2 */ ENAN_MOUTH_2,
    /* 3 */ ENAN_MOUTH_MAX
} EnAnMouth;

typedef enum EnAnFace {
    /*  0 */ ENAN_FACE_0,
    /*  1 */ ENAN_FACE_1,
    /*  2 */ ENAN_FACE_2,
    /*  3 */ ENAN_FACE_3,
    /*  4 */ ENAN_FACE_4,
    /*  5 */ ENAN_FACE_5,
    /*  6 */ ENAN_FACE_6,
    /*  7 */ ENAN_FACE_7,
    /*  8 */ ENAN_FACE_8,
    /*  9 */ ENAN_FACE_9,
    /* 10 */ ENAN_FACE_MAX
} EnAnFace;

static s16 sMouthIndices[ENAN_FACE_MAX] = {
    ENAN_MOUTH_0,     // ENAN_FACE_0
    ENAN_MOUTH_2,     // ENAN_FACE_1
    ENAN_MOUTH_0,     // ENAN_FACE_2
    ENAN_MOUTH_HAPPY, // ENAN_FACE_3
    ENAN_MOUTH_2,     // ENAN_FACE_4
    ENAN_MOUTH_0,     // ENAN_FACE_5
    ENAN_MOUTH_HAPPY, // ENAN_FACE_6
    ENAN_MOUTH_2,     // ENAN_FACE_7
    ENAN_MOUTH_HAPPY, // ENAN_FACE_8
    ENAN_MOUTH_HAPPY, // ENAN_FACE_9
};

void EnAn_UpdateFace(EnAn* this) {
    s32 skipBlink = false;

    if (this->stateFlags & ENAN_STATE_UPDATE_EYES) {
        if (DECR(this->eyeTimer) == 0) {
            // default case doesn't match
            switch (this->faceIndex) {
                case ENAN_FACE_2:
                case ENAN_FACE_4:
                case ENAN_FACE_6:
                    if ((this->eyeTexIndex == ENAN_EYES_SAD) || (this->eyeTexIndex == ENAN_EYES_CLOSED)) {
                        skipBlink = true;
                        this->eyeTexIndex = ENAN_EYES_SAD;
                    }
                    break;

                case ENAN_FACE_5:
                case ENAN_FACE_7:
                    if ((this->eyeTexIndex == ENAN_EYES_ANGRY) || (this->eyeTexIndex == ENAN_EYES_HALF1)) {
                        skipBlink = true;
                        this->eyeTexIndex = ENAN_EYES_ANGRY;
                    }
                    break;

                case ENAN_FACE_8:
                    if ((this->eyeTexIndex == ENAN_EYES_4) || (this->eyeTexIndex == ENAN_EYES_CLOSED)) {
                        skipBlink = true;
                        this->eyeTexIndex = ENAN_EYES_4;
                    }
                    break;
            }

            if (!skipBlink) {
                if ((this->eyeTexIndex == ENAN_EYES_4) || (this->eyeTexIndex == ENAN_EYES_SAD)) {
                    this->eyeTexIndex = ENAN_EYES_OPEN;
                } else if (this->eyeTexIndex == ENAN_EYES_ANGRY) {
                    this->eyeTexIndex = ENAN_EYES_HALF1;
                }
            }

            if (!skipBlink) {
                this->eyeTexIndex++;

                if (this->eyeTexIndex > ENAN_EYES_HALF2) {
                    if ((this->faceIndex == ENAN_FACE_0) || (this->faceIndex == ENAN_FACE_1) ||
                        (this->faceIndex == ENAN_FACE_3)) {
                        this->eyeTimer = Rand_S16Offset(0x1E, 0x1E);
                    } else {
                        this->eyeTimer = 8;
                    }
                    this->eyeTexIndex = ENAN_EYES_OPEN;
                }
            }
        }
    }

    this->mouthTexIndex = sMouthIndices[this->faceIndex];
}

typedef enum EnAnAccessory {
    /* 0 */ ENAN_ACCESSORY_FOOD_TRAY,
    /* 1 */ ENAN_ACCESSORY_KAFEI_MASK,
    /* 2 */ ENAN_ACCESSORY_UMBRELLA,
    /* 3 */ ENAN_ACCESSORY_BROOM,
    /* 4 */ ENAN_ACCESSORY_CHOPSTICKS,
    /* 5 */ ENAN_ACCESSORY_MOON_MASK
} EnAnAccessory;

void EnAn_DrawAccessory(EnAn* this, PlayState* play, EnAnAccessory accessoryId) {
    s32 pad;
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Push();

    switch (accessoryId) {
        case ENAN_ACCESSORY_FOOD_TRAY:
            if ((this->stateFlags & ENAN_STATE_DRAW_TRAY) && !this->forceDraw) {
                this->unk_3A8++;
                this->unk_3AC -= 2;
                Gfx_SetupDL25_Xlu(play->state.gfxCtx);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPSegment(
                    POLY_XLU_DISP++, 0x08,
                    Gfx_TwoTexScroll(play->state.gfxCtx, 0, this->unk_3A8, 0, 16, 16, 1, 0, this->unk_3AC, 16, 16));
                gSPDisplayList(POLY_XLU_DISP++, gAnju1FoodTrayDL);

                Gfx_SetupDL25_Opa(play->state.gfxCtx);
            }
            break;

        case ENAN_ACCESSORY_KAFEI_MASK:
            otherObjectSlot = this->maskKerfayObjectSlot;
            if ((this->stateFlags & ENAN_STATE_DRAW_KAFEI_MASK) && !this->forceDraw &&
                (otherObjectSlot > OBJECT_SLOT_NONE)) {
                static Vec3f D_80B58E54 = { 190.0f, -130.0f, 0.0f };
                static Vec3s D_80B58E60 = { 0, 0, 0x4168 };

                gSPSegment(POLY_OPA_DISP++, 0x0A, play->objectCtx.slots[otherObjectSlot].segment);

                Matrix_TranslateRotateZYX(&D_80B58E54, &D_80B58E60);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, gKafeiMaskDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case ENAN_ACCESSORY_UMBRELLA:
            otherObjectSlot = this->an2ObjectSlot;
            if ((this->stateFlags & ENAN_STATE_DRAW_UMBRELLA) && !this->forceDraw &&
                (otherObjectSlot > OBJECT_SLOT_NONE)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, gAnju2UmbrellaDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case ENAN_ACCESSORY_BROOM:
            otherObjectSlot = this->an3ObjectSlot;
            if ((this->stateFlags & ENAN_STATE_DRAW_BROOM) && !this->forceDraw &&
                (otherObjectSlot > OBJECT_SLOT_NONE)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, gAnju3BroomDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case ENAN_ACCESSORY_CHOPSTICKS:
            if ((this->stateFlags & ENAN_STATE_DRAW_CHOPSTICKS) && !this->forceDraw) {
                gSPDisplayList(POLY_OPA_DISP++, gAnju1ChopsticksDL);
            }
            break;

        case ENAN_ACCESSORY_MOON_MASK:
            otherObjectSlot = this->msmoObjectSlot;
            if (this->drawMoonMask && (otherObjectSlot > OBJECT_SLOT_NONE)) {
                static Vec3f D_80B58E68 = { 450.0f, 700.0f, -760.0f };
                static Vec3s D_80B58E74 = { 0x238C, 0, -0x3FFC };

                Matrix_TranslateRotateZYX(&D_80B58E68, &D_80B58E74);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, gMoonMaskDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnAn_ChangeCutscene(EnAn* this, s16 csId) {
    s32 ret = false;

    if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(csId);
    } else if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_StartWithPlayerCs(csId, &this->actor);
        ret = true;
    } else {
        CutsceneManager_Queue(csId);
    }

    return ret;
}

s16 EnAn_GetCsId(EnAn* this, s32 numCutscenes) {
    s16 csId = this->actor.csId;
    s32 i;

    for (i = 0; i < numCutscenes; i++) {
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }

    return csId;
}

s16 EnAn_GetChildCsId(EnAn* this, s32 numCutscenes) {
    Actor* child = this->actor.child;
    s16 csId = -1;
    s32 i;

    if ((child != NULL) && (child->update != NULL)) {
        csId = child->csId;

        for (i = 0; i < numCutscenes; i++) {
            csId = CutsceneManager_GetAdditionalCsId(csId);
        }
    }

    return csId;
}

s32 EnAn_MsgEvent_ReceiveLetterFromPostman(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s16 csId = EnAn_GetCsId(this, 0);
    s32 ret = false;

    switch (this->msgEventState) {
        case 0x0:
            ret = false;
            if (EnAn_ChangeCutscene(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        case 0x6:
        label:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            ret = true;
            this->msgEventState++;
            break;

        case 0x1:
        case 0x3:
        case 0x5:
            if ((CHECK_WEEKEVENTREG(WEEKEVENTREG_86_08)) && (this->msgEventState == 3)) {
                CutsceneManager_Stop(csId);
            } else if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            this->msgEventState++;
            ret = true;
            break;

        case 0x7:
            CutsceneManager_Stop(csId);
            ret = true;
            this->msgEventState++;
            break;
    }

    return ret;
}

s32 EnAn_MsgEvent_AttendGoron(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s16 csId = EnAn_GetCsId(this, 0);
    s32 ret = false;

    switch (this->msgEventState) {
        case 0x0:
            ret = false;
            if (EnAn_ChangeCutscene(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        label:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            ret = true;
            this->msgEventState++;
            break;

        case 0x1:
        case 0x3:
            if (!(CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_ROOM_KEY)) && (this->msgEventState == 3)) {
                CutsceneManager_Stop(csId);
                this->msgEventState = 5;
            } else if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            this->msgEventState++;
            ret = true;
            break;

        case 0x5:
            CutsceneManager_Stop(csId);
            ret = true;
            this->msgEventState++;
            break;
    }

    return ret;
}

s32 EnAn_MsgEvent_GiveLunchToGranny(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s16 csId = EnAn_GetChildCsId(this, 0);
    s32 ret = 0;

    switch (this->msgEventState) {
        case 0x0:
            ret = 0;
            if (EnAn_ChangeCutscene(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        case 0x6:
        case 0x8:
        label:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            ret = 1;
            this->msgEventState++;
            break;

        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            ret = 1;
            this->msgEventState++;
            break;

        case 0x9:
            CutsceneManager_Stop(csId);
            ret = 1;
            this->msgEventState++;
            break;
    }

    return ret;
}

// Only used if Player is using Kafei's Mask or if Human and Promised midnight meeting
s32 EnAn_MsgEvent_MidnightMeeting(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if (this->msgEventState == 0) {
        func_800B7298(play, &this->actor, PLAYER_CSMODE_WAIT);
        play->nextEntrance = ENTRANCE(STOCK_POT_INN, 3);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_FADE_BLACK;
        gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK_SLOW;
        this->msgEventState++;
    }
    return 0;
}

s32 EnAn_MsgEvent_Cooking(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s32 sp20 = false;

    switch (this->msgEventState) {
        case 0x0:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_TASTING);
            this->msgEventState++;
            break;

        case 0x1:
        case 0x3:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->msgEventState++;
                sp20 = true;
            }
            break;

        case 0x2:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_TASTING_END);
            this->msgEventState++;
            break;
    }

    return sp20;
}

s32 EnAn_MsgEvent_LaundryPool(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s32 ret = false;

    switch (this->msgEventState) {
        case 0x0:
            if ((Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) || CHECK_WEEKEVENTREG(WEEKEVENTREG_55_20)) {
                this->msgEventState++;
                goto label;
            } else {
                ret = true;
                this->stateFlags |= ENAN_STATE_DRAW_KAFEI_MASK;
                this->msgEventState++;
            }
            break;

        case 0x1:
        label:
            this->stateFlags &= ~(ENAN_STATE_20 | ENAN_STATE_DRAW_KAFEI_MASK);
            this->stateFlags |= ENAN_STATE_200;
            EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_CRYING);
            ret = true;
            this->msgEventState++;
            break;
    }

    return ret;
}

// TODO: figure out what to do with this
#define SCHEDULE_CALC_TIME_ALT(hour, minute) SCHEDULE_CONVERT_TIME((((hour)*60.0f) + (minute)) * (0x10000 / 60 / 24.0f))

s32* EnAn_GetMsgEventScript(EnAn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (this->scheduleResult) {
        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            this->msgEventFunc = EnAn_MsgEvent_GiveLunchToGranny;
            return sAnjuMsgScript_SchGiveLunchToGranny;

        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
            this->msgEventFunc = EnAn_MsgEvent_ReceiveLetterFromPostman;
            return sAnjuMsgScript_SchReceiveLetterFromPostman;

        case ANJU_SCH_ATTEND_GORON:
            this->msgEventFunc = EnAn_MsgEvent_AttendGoron;
            return sAnjuMsgScript_SchAttendGoron;

        case ANJU_SCH_COOKING:
            this->msgEventFunc = EnAn_MsgEvent_Cooking;
            return sAnjuMsgScript_SchCooking;

        case ANJU_SCH_RANCH:
            return sAnjuMsgScript_SchRanch;

        case ANJU_SCH_WITH_KAFEI:
            return sAnjuMsgScript_SchWithKafei;

        default:
            break;
    }

    if (player->transformation == PLAYER_FORM_DEKU) {
        switch (this->scheduleResult) {
            case ANJU_SCH_WAITING_FOR_KAFEI:
                return sAnjuMsgScript_SchWaitingForKafei;

            case ANJU_SCH_WALKING_40:
            case ANJU_SCH_WALKING_42:
            case ANJU_SCH_WALKING_43:
            case ANJU_SCH_WALKING_44:
            case ANJU_SCH_WALKING_45:
            case ANJU_SCH_WALKING_47:
                return sAnjuMsgScript_80B58B7C;

            case ANJU_SCH_LAUNDRY_POOL_SIT:
                return sAnjuMsgScript_SchLaundryPoolDeku;

            case ANJU_SCH_WALKING_49:
                return sAnjuMsgScript_80B589FC;

            default:
                break;
        }

        return sAnjuMsgScript_DekuDefault;
    }

    if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        if (this->scheduleResult == ANJU_SCH_WALKING_49) {
            return sAnjuMsgScript_80B58B88;
        }

        if (this->scheduleResult == ANJU_SCH_MIDNIGHT_MEETING) {
            this->msgEventFunc = EnAn_MsgEvent_MidnightMeeting;
            return sAnjuMsgScript_SchMidnightMeeting;
        }

        if (this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) {
            this->msgEventFunc = EnAn_MsgEvent_LaundryPool;
            return sAnjuMsgScript_SchLaundryPoolKafeiMask;
        }

        if (gSaveContext.save.day >= 2) {
            return sAnjuMsgScript_80B58A44;
        }

        // if ((gSaveContext.save.time - 0x3FFC) < 0x5883) {
        // if (SCHEDULE_CONVERT_TIME_ALT(gSaveContext.save.time) < SCHEDULE_CONVERT_TIME_ALT(CLOCK_TIME(14,
        // 18))) {
        if (SCHEDULE_CONVERT_TIME_ALT(gSaveContext.save.time) < SCHEDULE_CALC_TIME_ALT(14, 18)) {
            return sAnjuMsgScript_80B58ABC;
        }

        return sAnjuMsgScript_80B58AC4;
    }

    if ((player->transformation == PLAYER_FORM_HUMAN) && CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        if (this->scheduleResult == ANJU_SCH_MIDNIGHT_MEETING) {
            this->msgEventFunc = EnAn_MsgEvent_MidnightMeeting;
            return sAnjuMsgScript_SchMidnightMeeting;
        }

        if (this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) {
            this->msgEventFunc = EnAn_MsgEvent_LaundryPool;
            return sAnjuMsgScript_SchLaundryPoolDefault;
        }

        if (gSaveContext.save.day >= 2) {
            return sAnjuMsgScript_80B58A44;
        }
    }

    switch (this->scheduleResult) {
        case ANJU_SCH_WAITING_FOR_KAFEI:
            return sAnjuMsgScript_SchWaitingForKafei;

        case ANJU_SCH_WALKING_40:
            return sAnjuMsgScript_80B5894C;

        case ANJU_SCH_WALKING_42:
        case ANJU_SCH_WALKING_43:
        case ANJU_SCH_WALKING_44:
        case ANJU_SCH_WALKING_45:
            return sAnjuMsgScript_80B58980;

        case ANJU_SCH_LAUNDRY_POOL_SIT:
            this->msgEventFunc = EnAn_MsgEvent_LaundryPool;
            return sAnjuMsgScript_SchLaundryPoolDefault;

        case ANJU_SCH_RECEPTIONIST_IDLE:
            if (gSaveContext.save.day >= 2) {
                return sAnjuMsgScript_80B58A3C;
            }
            return sAnjuMsgScript_80B5885C;

        case ANJU_SCH_WAITING_CLOSING_TIME:
        case ANJU_SCH_WALKING_47:
            return sAnjuMsgScript_InnCloseTime;

        case ANJU_SCH_SWEEPING:
            return sAnjuMsgScript_SchSweeping;

        case ANJU_SCH_MIDNIGHT_MEETING:
            return sAnjuMsgScript_80B589FC;

        case ANJU_SCH_WALKING_48:
            return sAnjuMsgScript_80B58944;

        case ANJU_SCH_WALKING_49:
            if (player->transformation == PLAYER_FORM_HUMAN) {
                return sAnjuMsgScript_80B58B88;
            }
            return sAnjuMsgScript_80B589FC;

        case ANJU_SCH_WALKING_52:
        case ANJU_SCH_WALKING_53:
            return sAnjuMsgScript_80B58994;

        default:
            break;
    }

    return NULL;
}

s32 EnAn_CheckTalk(EnAn* this, PlayState* play) {
    s32 ret = false;

    if ((this->stateFlags & SUBS_OFFER_MODE_MASK) && Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
        this->unk_3C4 = 0;
        this->msgEventState = 0;
        this->msgEventFunc = NULL;
        this->actor.child = this->lookAtActor;
        this->msgEventScript = EnAn_GetMsgEventScript(this, play);

        if ((this->scheduleResult == ANJU_SCH_WAITING_FOR_KAFEI) ||
            (this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) ||
            (this->scheduleResult == ANJU_SCH_RECEPTIONIST_IDLE) ||
            (this->scheduleResult == ANJU_SCH_WAITING_CLOSING_TIME) ||
            (this->scheduleResult == ANJU_SCH_MIDNIGHT_MEETING) || (this->scheduleResult == ANJU_SCH_SWEEPING) ||
            (this->scheduleResult == ANJU_SCH_WALKING_40) || (this->scheduleResult == ANJU_SCH_WALKING_42) ||
            (this->scheduleResult == ANJU_SCH_WALKING_43) || (this->scheduleResult == ANJU_SCH_WALKING_44) ||
            (this->scheduleResult == ANJU_SCH_WALKING_45) || (this->scheduleResult == ANJU_SCH_WALKING_47) ||
            (this->scheduleResult == ANJU_SCH_WALKING_48) || (this->scheduleResult == ANJU_SCH_WALKING_49) ||
            (this->scheduleResult == ANJU_SCH_WALKING_52) || (this->scheduleResult == ANJU_SCH_WALKING_53)) {
            this->stateFlags |= ENAN_STATE_20;
        }

        if ((this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) && CHECK_WEEKEVENTREG(WEEKEVENTREG_55_20)) {
            this->stateFlags &= ~ENAN_STATE_20;
        }

        this->actionFunc = EnAn_Talk;
        ret = true;
    }

    return ret;
}

s32 func_80B552E4(EnAn* this, PlayState* play) {
    u16 scriptIndex = play->csCtx.scriptIndex;
    s32 ret = false;

    if ((play->csCtx.state != CS_STATE_IDLE) && (play->sceneId == SCENE_YADOYA) && (gSaveContext.sceneLayer == 0) &&
        ((scriptIndex == 0) || (scriptIndex == 1))) {
        if (!this->forceDraw) {
            this->savedFaceIndex = ENAN_FACE_0;
            this->faceIndex = ENAN_FACE_0;
            this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
            this->eyeTimer = 8;
            this->cueId = -1;
            this->forceDraw = true;
            this->drawMoonMask = false;
        }

        ret = true;
    } else if (this->forceDraw) {
        this->forceDraw = false;
        this->drawMoonMask = false;
        this->unk_3C0 = true;
        this->actor.room = play->roomCtx.curRoom.num;
        this->actionFunc = EnAn_FollowSchedule;
    }

    return ret;
}

void EnAn_UpdateHeadRot(EnAn* this) {
    Actor* temp_v0_2;
    Vec3f sp40;
    Vec3f sp34;
    Player* player;

    Math_Vec3f_Copy(&sp40, &this->lookAtActor->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->headRotY, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->headRotY = CLAMP(this->headRotY, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    temp_v0_2 = this->lookAtActor;
    if (temp_v0_2->id == ACTOR_PLAYER) {
        player = (Player*)temp_v0_2;

        sp40.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &temp_v0_2->focus.pos);
    }

    Math_ApproachS(&this->headRotZ, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);

    this->headRotZ = CLAMP(this->headRotZ, -0x1554, 0x1554);
}

void func_80B554E8(EnAn* this) {
    if (this->stateFlags & ENAN_STATE_20) {
        if ((this->lookAtActor != NULL) && (this->lookAtActor->update != NULL)) {
            if (DECR(this->unk_388) == 0) {
                EnAn_UpdateHeadRot(this);
                this->stateFlags &= ~ENAN_STATE_200;
                this->stateFlags |= ENAN_STATE_80;
                return;
            }
        }
    }

    if (this->stateFlags & ENAN_STATE_80) {
        this->stateFlags &= ~ENAN_STATE_80;
        this->headRotZ = 0;
        this->headRotY = 0;
        this->unk_388 = 20;
        return;
    }

    if (DECR(this->unk_388) == 0) {
        this->stateFlags |= ENAN_STATE_200;
    }
}

s32 EnAn_ChooseAnimAfterTalking(EnAn* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
        case ANJU_SCH_ATTEND_GORON:
        case ANJU_SCH_RECEPTIONIST_IDLE:
        case ANJU_SCH_WAITING_CLOSING_TIME:
        case ANJU_SCH_MIDNIGHT_MEETING:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE);
            break;

        case ANJU_SCH_SWEEPING:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_BROOM_SWEEP);
            this->stateFlags |= ENAN_STATE_DRAW_BROOM;
            break;

        case ANJU_SCH_COOKING:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_COOKING);
            break;

        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_WAITING_WITH_TRAY);
            break;

        case ANJU_SCH_WALKING_47:
        case ANJU_SCH_WALKING_49:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_WALK);
            break;

        case ANJU_SCH_WALKING_52:
        case ANJU_SCH_WALKING_53:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_BROOM_WALK);
            this->stateFlags |= ENAN_STATE_DRAW_BROOM;
            break;

        default:
            if (this->animIndex == ENAN_ANIM_WAITING_WITH_TRAY) {
                EnAn_ChangeAnim(this, play, ENAN_ANIM_WALKING_WITH_TRAY);
            }
            if (this->animIndex == ENAN_ANIM_UMBRELLA_IDLE) {
                EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_WALK);
            }
            if ((this->animIndex == ENAN_ANIM_IDLE) || (this->animIndex == ENAN_ANIM_IDLE_MORPH)) {
                EnAn_ChangeAnim(this, play, ENAN_ANIM_WALK2);
            }
            break;
    }

    return 0;
}

void EnAn_DialogueFunc_80B556F8(EnAn* this, PlayState* play) {
    if (this->dialogueFuncState == 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_LOOKING_UP_RELIEVED);
        this->stateFlags &= ~ENAN_STATE_20;
        this->stateFlags |= ENAN_STATE_200;
        this->dialogueFuncState++;
    } else if ((this->dialogueFuncState == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE_MORPH);
        this->stateFlags &= ~ENAN_STATE_200;
        this->stateFlags |= ENAN_STATE_20;
        this->dialogueFuncState++;
    }
}

void EnAn_DialogueFunc_80B557AC(EnAn* this, PlayState* play) {
    if (this->dialogueFuncState == 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_BOWING);
        this->stateFlags &= ~ENAN_STATE_20;
        this->stateFlags |= ENAN_STATE_200;
        this->dialogueFuncState++;
    } else if ((this->dialogueFuncState == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE_MORPH);
        this->stateFlags &= ~ENAN_STATE_200;
        this->stateFlags |= ENAN_STATE_20;
        this->dialogueFuncState++;
    }
}

void EnAn_DialogueFunc_80B55860(EnAn* this, PlayState* play) {
    if (this->dialogueFuncState == 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_BOWING_MORPH);
        this->stateFlags |= ENAN_STATE_200;
        this->stateFlags &= ~ENAN_STATE_20;
        this->dialogueFuncState++;
    } else if ((this->dialogueFuncState == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE_MORPH);
        this->stateFlags &= ~ENAN_STATE_200;
        this->stateFlags |= ENAN_STATE_20;
        this->dialogueFuncState++;
    }
}

s32 EnAn_HandleDialogue(EnAn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 textId = play->msgCtx.currentTextId;

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        this->stateFlags |= ENAN_STATE_TALKING;

        if (this->prevTextId != textId) {
            switch (textId) {
                case 0x28E5: // "Ah!"
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_SURPRISED);
                    this->stateFlags &= ~ENAN_STATE_DRAW_BROOM;
                    break;

                case 0x28BA: // "What's this?"
                case 0x28D1: // "You are looking for Kafei?"
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_SURPRISED);
                    break;

                case 0x28AF: // "Good night"
                case 0x28C1: // "I need to hurry and cook for grandmother"
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE);
                    break;

                case 0x28BC: // "Where did you got that letter?"
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE_MORPH);
                    break;

                case 0x28C6: // "Don't talk to me or I'll drop this plate"
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_WAITING_WITH_TRAY);
                    break;

                case 0x28F5: // "The town will be crushed by the moon. Forget about the letter"
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_SIT_MORPH);
                    break;

                case 0x28F7: // "Everyone will be taking refuge by tomorrow"
                case 0x28F8: // "We'll go to Romani Ranch to take refuge"
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_BROOM_IDLE);
                    break;

                case 0x28EB: // "I'm afraid to meet him..."
                    if (this->animIndex != ENAN_ANIM_UMBRELLA_CRYING) {
                        this->stateFlags &= ~(ENAN_STATE_20 | ENAN_STATE_DRAW_KAFEI_MASK);
                        this->stateFlags |= ENAN_STATE_200;
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_CRYING);
                    }
                    break;

                case 0x28A4: // "That's good. We're totally booked right before the carnival"
                case 0x28A9: // "You do have a reservation?"
                case 0x28BE: // "From what postbox did you got that letter?!"
                case 0x28C0: // "Not what I mean!"
                case 0x295E: // "I need to know!"
                    this->dialogueFunc = EnAn_DialogueFunc_80B556F8;
                    this->dialogueFuncState = 0;
                    break;

                case 0x28E6: // "It's from Kafei"
                    this->stateFlags &= ~ENAN_STATE_DRAW_BROOM;
                    this->dialogueFunc = EnAn_DialogueFunc_80B55860;
                    this->dialogueFuncState = 0;
                    break;

                case 0x1885: // "It's 8:30 pm and the Inn is locking the door"
                case 0x28A0: // "Welcome to the Inn."
                case 0x28A3: // "I'm sorry, there are no vacancies. We are always booked at the carnival"
                case 0x28A5: // "Visit us again in the future"
                case 0x28B1: // "I'm sorry, there are no vacancies"
                case 0x28D2: // "I have a clue that will help find Kafei"
                case 0x28D9: // "Please"
                case 0x28DC: // "Thank you"
                case 0x28DE: // "Mail it in the morning"
                    this->dialogueFunc = EnAn_DialogueFunc_80B557AC;
                    this->dialogueFuncState = 0;
                    break;

                case 0x28A1: // "Are you staying the night?"
                case 0x28A2: // "You are staying the night!?"
                case 0x28A6: // "Are you staying the night? Did I ask you the same earlier?"
                case 0x28A7: // "Enjoy the carnival"
                case 0x28A8: // "Did you have a reservation?"
                case 0x28AA: // "One moment please"
                case 0x28AB: // "I expected your arrival for afternon. Your room is on the second floor"
                case 0x28AC: // "Have you been to the plaza yet? They are putting the carnival stuff"
                case 0x28AD: // "Relax..."
                case 0x28AE: // doesn't exist
                case 0x28B0: // "It's hard to find one's way on the city goro"
                case 0x28B2: // "I should have a reservation-goro"
                case 0x28B3: // "I do have your reservation. Your room is on the second floor"
                case 0x28B4: // "The place is falling apart-goro"
                case 0x28B5: // "I made a reservation. I'm [Player]-goro"
                case 0x28B6: // "[Player]-goro? There's a reservation under a similar name, but it's taken"
                case 0x28B7: // "Really-goro? I'll just sleep outside then-goro"
                case 0x28B8: // "I'm sorry"
                case 0x28B9: // "It's a hard world-goro"
                case 0x28BB: // "I delivered this to you!"
                case 0x28BD: // "From the postbox"
                case 0x28BF: // "From somewhere"
                case 0x28C2: // "I need to hurry! The afternoon guest will arrive soon"
                case 0x28C3: // "Used to be a cafeteria"
                case 0x28C4:
                case 0x28C5: // "Mmm?"
                case 0x28C7: // "Tortus, I've already had lunch"
                case 0x28C8: // "I'm Anju! Tortus was my dad..."
                case 0x28C9: // "I've already had lunch"
                case 0x28CA: // "Please eat..."
                case 0x28CB: // "I already ate lunch"
                case 0x28CC: // "Don't eat my food then"
                case 0x28CD: // "Phew"
                case 0x28CE: // "Phew?"
                case 0x28CF: // "Want me to read a story?"
                case 0x28D0: // "That mask... You are looking for Kafei"
                case 0x28D3: // "Come to our kitchen at 11:30"
                case 0x28D4: // "I'll find him myself"
                case 0x28D5: // "I wonder where Kafei could have gone"
                case 0x28D6: // "Nevermind!"
                case 0x28D7: // "I'm sorry to bother you late at night"
                case 0x28D8: // "I received a letter from Kafei"
                case 0x28DA: // "Put my letter in a postbox"
                case 0x28DB: // "Can I ask this to you?"
                case 0x28DD: // doesn't exist
                case 0x28DF: // "You won't take refuge?"
                case 0x28E0: // "Today's weather"
                case 0x28E1: // "I'll wait for him"
                case 0x28E2: // "Did you see him? It's too late"
                case 0x28E3: // "Did you see him? It's too early"
                case 0x28E4: // "Did you meet him?"
                case 0x28E7: // "What's that?"
                case 0x28E8: // "Have you seen a man around here?"
                case 0x28E9: // "He looks like this"
                case 0x28EA: // "He disappeared a month ago"
                case 0x28EC: // "Should I wait?"
                case 0x28ED: // "You are looking for him too"
                case 0x28EE: // "I came here to look for him myself"
                case 0x28EF: // "What a ramshackle inn"
                case 0x28F0: // "Everything is falling apart"
                case 0x28F1: // "We are leaving in the evening for the ranch"
                case 0x28F2: // "I wonder if Kafei is really at Cremia's"
                case 0x28F3:
                case 0x28F4: // "But he said in the letter he'll come back"
                case 0x28F6: // "Mother thank you"
                default:
                    if (this->animIndex == ENAN_ANIM_WALKING_WITH_TRAY) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_WAITING_WITH_TRAY);
                    }
                    if (this->animIndex == ENAN_ANIM_UMBRELLA_WALK) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_IDLE);
                    }
                    if ((this->animIndex == ENAN_ANIM_BROOM_WALK) || (this->animIndex == ENAN_ANIM_BROOM_SWEEP)) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_BROOM_IDLE);
                    }
                    if ((this->animIndex == ENAN_ANIM_WALK) || (this->animIndex == ENAN_ANIM_WALK2)) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE_MORPH);
                    }
                    break;
            }

            switch (textId) {
                case 0x28F5: // "The town will be crushed by the moon. Forget about the letter"
                    this->savedFaceIndex = ENAN_FACE_0;
                    /* fallthrough */
                case 0x28A5: // "Visit us again in the future"
                case 0x28AA: // "One moment please"
                case 0x28F8: // "We'll go to Romani Ranch to take refuge"
                    this->faceIndex = ENAN_FACE_0;
                    this->eyeTimer = 8;
                    break;

                case 0x1885: // "It's 8:30 pm and the Inn is locking the door"
                case 0x28A0: // "Welcome to the Inn."
                case 0x28A6: // "Are you staying the night? Did I ask you the same earlier?"
                case 0x28AF: // "Good night"
                case 0x28C1: // "I need to hurry and cook for grandmother"
                    this->faceIndex = ENAN_FACE_3;
                    this->eyeTimer = 8;
                    break;

                case 0x28A2: // "You are staying the night!?"
                case 0x28B3: // "I do have your reservation. Your room is on the second floor"
                case 0x28B6: // "[Player]-goro? There's a reservation under a similar name, but it's taken"
                case 0x28BA: // "What's this?"
                case 0x28BE: // "From what postbox did you got that letter?!"
                case 0x28CE: // "Phew?"
                case 0x28D0: // "That mask... You are looking for Kafei"
                case 0x28D6: // "Nevermind!"
                case 0x28E5: // "Ah!"
                case 0x28E7: // "What's that?"
                case 0x28ED: // "You are looking for him too"
                    this->faceIndex = ENAN_FACE_1;
                    this->eyeTimer = 8;
                    break;

                case 0x28AD: // "Relax..."
                    this->faceIndex = ENAN_FACE_8;
                    this->eyeTimer = 8;
                    break;

                case 0x28C0: // "Not what I mean!"
                case 0x28D7: // "I'm sorry to bother you late at night"
                case 0x28DE: // "Mail it in the morning"
                    this->faceIndex = ENAN_FACE_2;
                    this->eyeTimer = 8;
                    break;

                case 0x28E6: // "It's from Kafei"
                case 0x28F7: // "Everyone will be taking refuge by tomorrow"
                    this->faceIndex = ENAN_FACE_6;
                    this->eyeTimer = 8;
                    break;

                case 0x28A3: // "I'm sorry, there are no vacancies. We are always booked at the carnival"
                case 0x28B1: // "I'm sorry, there are no vacancies"
                case 0x28B8: // "I'm sorry"
                case 0x28C6: // "Don't talk to me or I'll drop this plate"
                case 0x28CA: // "Please eat..."
                case 0x28CC: // "Don't eat my food then"
                case 0x28D5: // "I wonder where Kafei could have gone"
                case 0x28E2: // "Did you see him? It's too late"
                case 0x28E3: // "Did you see him? It's too early"
                case 0x28E4: // "Did you meet him?"
                    this->faceIndex = ENAN_FACE_4;
                    this->eyeTimer = 8;
                    break;

                case 0x28EC: // "Should I wait?"
                    this->savedFaceIndex = ENAN_FACE_5;
                    /* fallthrough */
                case 0x28DC: // "Thank you"
                case 0x28EB: // "I'm afraid to meet him..."
                case 0x28F2: // "I wonder if Kafei is really at Cremia's"
                case 0x28F9: // "Perhaps I was wrong..."
                    this->faceIndex = ENAN_FACE_5;
                    this->eyeTimer = 8;
                    break;

                case 0x28F6: // "Mother thank you"
                    this->faceIndex = ENAN_FACE_9;
                    this->eyeTimer = 8;
                    break;

                case 0x28A4: // "That's good. We're totally booked right before the carnival"
                case 0x28A9: // "You do have a reservation?"
                    this->faceIndex = ENAN_FACE_7;
                    this->eyeTimer = 8;
                    break;
            }
        }

        this->prevTextId = textId;
    } else if (this->stateFlags & ENAN_STATE_TALKING) {
        // Player stopped talking with Anju

        this->dialogueFunc = NULL;
        this->prevTextId = 0;
        this->stateFlags &= ~ENAN_STATE_TALKING;
        this->faceIndex = this->savedFaceIndex;
        this->eyeTimer = 4;
        EnAn_ChooseAnimAfterTalking(this, play);
    }

    if (this->dialogueFunc != NULL) {
        this->dialogueFunc(this, play);
    }

    return 0;
}

Actor* EnAn_FindLookAtActor(EnAn* this, PlayState* play) {
    Actor* actor;

    switch (this->scheduleResult) {
        default:
            actor = &GET_PLAYER(play)->actor;
            break;

        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            actor = EnAn_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_NB);
            break;

        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
            actor = EnAn_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_PM);
            break;

        case ANJU_SCH_ATTEND_GORON:
            actor = EnAn_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_IG);
            break;
    }

    return actor;
}

s32 func_80B55D98(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput, u8 actorCategory, s16 actorId) {
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    Vec3s* points;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* actor;
    s32 limit;
    s32 ret = false;

    actor = EnAn_FindActor(this, play, actorCategory, actorId);
    this->timePath = NULL;

    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((actor != NULL) && (actor->update != NULL)) {
        if (this->timePath != NULL) {
            points = Lib_SegmentedToVirtual(this->timePath->points);
            Math_Vec3s_ToVec3f(&sp3C, &points[this->timePath->count - 2]);
            Math_Vec3s_ToVec3f(&sp30, &points[this->timePath->count - 1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            ret = true;
        }
    }

    return ret;
}

s32 EnAn_IsFacingAndNearPlayer(EnAn* this) {
    s32 ret = false;

    // TODO: why is the range variable?
    if (Actor_IsFacingAndNearPlayer(&this->actor, this->unk_3BC ? 150.0f : 100.0f, 0x2800)) {
        ret = true;
    }

    if (DECR(this->unk_386) == 0) {
        this->unk_3BC ^= 1;
        this->unk_386 = Rand_S16Offset(60, 60); // 3~6 seconds
    }

    return ret;
}

s32 func_80B55F8C(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 ret = false;

    if ((Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) &&
        CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        ret = true;
    } else if ((player->transformation == PLAYER_FORM_HUMAN) &&
               CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        ret = true;
    }

    return ret;
}

s32 EnAn_ProcessSchedule_ReceiveLetterFromPostman(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_PM)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE);
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        ret = true;

        this->stateFlags |= ENAN_STATE_20 | ENAN_STATE_UPDATE_EYES;
        this->stateFlags |= ENAN_STATE_200;
    }

    return ret;
}

s32 EnAn_ProcessSchedule_AttendGoron(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_IG)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE);
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        ret = true;

        this->stateFlags |= ENAN_STATE_20 | ENAN_STATE_UPDATE_EYES;
        this->stateFlags |= ENAN_STATE_200;
    }

    return ret;
}

s32 EnAn_ProcessSchedule_GiveLunchToGranny(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_NB)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_WAITING_WITH_TRAY);
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        ret = true;

        this->stateFlags |= ENAN_STATE_20 | ENAN_STATE_UPDATE_EYES;
        this->stateFlags |= ENAN_STATE_200 | ENAN_STATE_DRAW_TRAY;
    }

    return ret;
}

s32 EnAn_ProcessSchedule_Door(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 now = SCHEDULE_TIME_NOW;
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    EnDoor* door;
    Vec3s* points;
    Vec3f firstPos;
    Vec3f secondPos;
    s32 limit;
    s32 ret = false;

    this->timePath = NULL;
    door = EnAn_FindDoor(play, scheduleOutput->result);

    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((door != NULL) && (door->knobDoor.dyna.actor.update != NULL)) {
        if (this->timePath != NULL) {
            points = Lib_SegmentedToVirtual(this->timePath->points);
            Math_Vec3s_ToVec3f(&firstPos, &points[0]);
            Math_Vec3s_ToVec3f(&secondPos, &points[1]);

            Math_Vec3f_Copy(&this->doorEntrancePos, &firstPos);
            Math_Vec3f_Copy(&this->doorExitPos, &secondPos);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&firstPos, &secondPos);
            Math_Vec3f_Copy(&this->actor.world.pos, &firstPos);

            if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, door->knobDoor.dyna.actor.shape.rot.y)) <= 0x4000) {
                this->doorOpenTimer = -75;
            } else {
                this->doorOpenTimer = 75;
            }

            this->doorTimeTotalDiff = scheduleOutput->time1 - scheduleOutput->time0;
            this->var1.doorTimeProgress = now - scheduleOutput->time0;

            switch (scheduleOutput->result) {
                case ANJU_SCH_DOOR_27:
                case ANJU_SCH_DOOR_28:
                case ANJU_SCH_DOOR_32:
                case ANJU_SCH_DOOR_33:
                case ANJU_SCH_DOOR_34:
                case ANJU_SCH_DOOR_35:
                case ANJU_SCH_DOOR_37:
                case ANJU_SCH_DOOR_38:
                    this->savedFaceIndex = ENAN_FACE_2;
                    this->faceIndex = ENAN_FACE_2;
                    this->eyeTimer = 8;
                    break;
            }

            switch (scheduleOutput->result) {
                case ANJU_SCH_DOOR_26:
                case ANJU_SCH_DOOR_27:
                case ANJU_SCH_DOOR_28:
                    this->stateFlags |= ENAN_STATE_DRAW_TRAY | ENAN_STATE_UPDATE_EYES;
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_WALKING_WITH_TRAY);
                    break;

                case ANJU_SCH_DOOR_36:
                case ANJU_SCH_DOOR_39:
                    this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_DRAW_BROOM;
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_BROOM_WALK);
                    break;

                default:
                    this->stateFlags |= ENAN_STATE_UPDATE_EYES;
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_WALK);
                    break;
            }

            this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
            this->stateFlags |= ENAN_STATE_200;
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }

    return ret;
}

s32 EnAn_ProcessSchedule_Walking(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 now = SCHEDULE_TIME_NOW;
    u16 startTime;
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    s32 pad;
    s32 ret = false;
    s32 limit;

    this->timePath = NULL;

    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->timePath != NULL) && (this->timePath->count < 3)) {
        this->timePath = NULL;
    }

    if (this->timePath != NULL) {
        if ((this->scheduleResult < ANJU_SCH_WALKING_40) && (this->scheduleResult != ANJU_SCH_NONE) &&
            (this->timePathTimeSpeed >= 0)) {
            startTime = now;
        } else {
            startTime = scheduleOutput->time0;
        }

        if (scheduleOutput->time1 < startTime) {
            this->timePathTotalTime = (startTime - scheduleOutput->time1) + 0xFFFF;
        } else {
            this->timePathTotalTime = scheduleOutput->time1 - startTime;
        }

        this->timePathElapsedTime = now - startTime;
        startTime = (this->timePath->count - 2);
        this->timePathWaypointTime = this->timePathTotalTime / startTime;

        this->timePathWaypoint = (this->timePathElapsedTime / this->timePathWaypointTime) + 2;
        this->stateFlags &= ~ENAN_STATE_8;
        this->stateFlags &= ~ENAN_STATE_REACHED_PATH_END;

        switch (scheduleOutput->result) {
            case ANJU_SCH_WALKING_44:
            case ANJU_SCH_WALKING_45:
            case ANJU_SCH_WALKING_50:
            case ANJU_SCH_WALKING_51:
            case ANJU_SCH_WALKING_54:
            case ANJU_SCH_WALKING_55:
            case ANJU_SCH_WALKING_56:
            case ANJU_SCH_WALKING_57:
            case ANJU_SCH_WALKING_58:
            case ANJU_SCH_WALKING_59:
            case ANJU_SCH_WALKING_60:
            case ANJU_SCH_WALKING_61:
            case ANJU_SCH_WALKING_62:
            case ANJU_SCH_WALKING_63:
                this->savedFaceIndex = ENAN_FACE_2;
                this->faceIndex = ENAN_FACE_2;
                this->eyeTimer = 8;
                break;
        }

        switch (scheduleOutput->result) {
            case ANJU_SCH_WALKING_42:
            case ANJU_SCH_WALKING_43:
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                /* fallthrough */
            case ANJU_SCH_WALKING_44:
            case ANJU_SCH_WALKING_45:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_WALKING_WITH_TRAY);
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                this->stateFlags |= ENAN_STATE_DRAW_TRAY;
                break;

            case ANJU_SCH_WALKING_52:
            case ANJU_SCH_WALKING_53:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_BROOM_WALK);
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                this->stateFlags |= ENAN_STATE_DRAW_BROOM;
                break;

            case ANJU_SCH_WALKING_50:
            case ANJU_SCH_WALKING_51:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_WALK);
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                break;

            case ANJU_SCH_WALKING_54:
            case ANJU_SCH_WALKING_55:
            case ANJU_SCH_WALKING_56:
            case ANJU_SCH_WALKING_57:
            case ANJU_SCH_WALKING_58:
            case ANJU_SCH_WALKING_59:
            case ANJU_SCH_WALKING_60:
            case ANJU_SCH_WALKING_61:
            case ANJU_SCH_WALKING_62:
            case ANJU_SCH_WALKING_63:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_WALK);
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                this->stateFlags |= ENAN_STATE_DRAW_UMBRELLA;
                break;

            case ANJU_SCH_WALKING_40:
            case ANJU_SCH_WALKING_47:
            case ANJU_SCH_WALKING_48:
            case ANJU_SCH_WALKING_49:
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                /* fallthrough */
            default:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_WALK);
                break;
        }

        ret = true;
        this->actor.gravity = -1.0f;
    }

    return ret;
}

s32 EnAn_ProcessSchedule_Sweeping(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    Vec3f firstPos;
    Vec3f secondPos;
    Vec3s* points;
    s32 limit;
    s32 ret = false;

    this->timePath = NULL;

    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->timePath != NULL) && (this->timePath->count >= 2)) {
        points = Lib_SegmentedToVirtual(this->timePath->points);
        Math_Vec3s_ToVec3f(&firstPos, &points[0]);
        Math_Vec3s_ToVec3f(&secondPos, &points[1]);

        this->actor.world.rot.y = Math_Vec3f_Yaw(&firstPos, &secondPos);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &firstPos);
        Math_Vec3f_Copy(&this->actor.prevPos, &firstPos);

        if (scheduleOutput->result == ANJU_SCH_SWEEPING) {
            EnAn_ChangeAnim(this, play, ENAN_ANIM_BROOM_SWEEP);
            SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

            this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
            this->stateFlags |= ENAN_STATE_DRAW_BROOM;
        }

        ret = true;
    }

    return ret;
}

s32 EnAn_ProcessSchedule_80B56880(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    Vec3f lastPos;
    Vec3f penultimatePos;
    Vec3s* points;
    s32 limit;
    s32 ret = false;

    this->timePath = NULL;
    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->timePath != NULL) && (this->timePath->count >= 2)) {
        points = Lib_SegmentedToVirtual(this->timePath->points);
        Math_Vec3s_ToVec3f(&lastPos, &points[this->timePath->count - 1]);
        Math_Vec3s_ToVec3f(&penultimatePos, &points[this->timePath->count - 2]);

        this->actor.world.rot.y = Math_Vec3f_Yaw(&penultimatePos, &lastPos);

        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3s_Copy(&this->actor.home.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &lastPos);
        Math_Vec3f_Copy(&this->actor.prevPos, &lastPos);

        switch (scheduleOutput->result) {
            case ANJU_SCH_WAITING_CLOSING_TIME:
                this->actor.world.rot.y += 0x7FF8;
                /* fallthrough */
            case ANJU_SCH_RECEPTIONIST_IDLE:
            case ANJU_SCH_MIDNIGHT_MEETING:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE);
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->var1.followScheduleState = 0;
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                if (scheduleOutput->result == ANJU_SCH_RECEPTIONIST_IDLE) {
                    this->unk_374 = 70.0f;
                }
                break;

            case ANJU_SCH_LAUNDRY_POOL_SIT:
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                this->stateFlags |= ENAN_STATE_DRAW_UMBRELLA;

                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_55_20)) {
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_CRYING);
                    this->stateFlags |= ENAN_STATE_IGNORE_GRAVITY;
                    this->actor.world.rot.y += 0x7FF8;
                    this->actor.shape.rot.y = this->actor.world.rot.y;
                    this->var1.laundryPoolState = 4;
                } else {
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_WALK);
                    this->var1.laundryPoolState = 0;
                }

                this->savedFaceIndex = ENAN_FACE_2;
                this->faceIndex = ENAN_FACE_2;
                this->eyeTimer = 8;
                break;

            case ANJU_SCH_COOKING:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_COOKING);
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
                this->stateFlags |= ENAN_STATE_DRAW_CHOPSTICKS;
                break;
        }
        ret = true;
    }

    return ret;
}

s32 EnAn_ProcessSchedule_Ranch(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    static Vec3f D_80B58E7C = { 905.0f, 260.0f, -64.0f };
    static Vec3s D_80B58E88 = { 0, 0, 0 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80B58E7C);
    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58E88);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);

    if (scheduleOutput->result == ANJU_SCH_RANCH) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_SITTING_IN_DISBELIEVE);
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

        this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
        this->stateFlags |= ENAN_STATE_IGNORE_GRAVITY;

        this->savedFaceIndex = ENAN_FACE_5;
        this->faceIndex = ENAN_FACE_5;
        this->eyeTimer = 8;
    }

    return true;
}

s32 EnAn_ProcessSchedule_StaffRoom(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    static Vec3f D_80B58E90 = { -508.0f, 210.0f, -162.0f };
    static Vec3s D_80B58E9C = { 0, 0x3FFC, 0 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80B58E90);
    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58E9C);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);

    switch (scheduleOutput->result) {
        case ANJU_SCH_WAITING_FOR_KAFEI:
            SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            EnAn_ChangeAnim(this, play, ENAN_ANIM_SIT);
            break;

        case ANJU_SCH_TALKING_WITH_MOM:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_SITTING_IN_DISBELIEVE);
            this->savedFaceIndex = ENAN_FACE_5;
            this->faceIndex = ENAN_FACE_5;
            this->eyeTimer = 8;
            break;
    }

    this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;
    this->stateFlags |= ENAN_STATE_IGNORE_GRAVITY;

    this->actor.gravity = 0.0f;
    return true;
}

s32 EnAn_ProcessSchedule_WithKafei(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    static Vec3s D_80B58EA4 = { 0, -0x2AAD, 0 };
    s32 pad;

    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58EA4);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);
    EnAn_ChangeAnim(this, play, ENAN_ANIM_HOLDING_HANDS);
    SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    this->stateFlags |= ENAN_STATE_UPDATE_EYES | ENAN_STATE_200;

    return true;
}

s32 EnAn_ProcessScheduleOutput(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret;

    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    this->actor.targetMode = TARGET_MODE_6;
    this->stateFlags = 0;
    this->savedFaceIndex = ENAN_FACE_0;
    this->faceIndex = ENAN_FACE_0;
    this->eyeTimer = 8;
    this->unk_374 = 40.0f;

    switch (scheduleOutput->result) {
        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
            ret = EnAn_ProcessSchedule_ReceiveLetterFromPostman(this, play, scheduleOutput);
            break;

        case ANJU_SCH_ATTEND_GORON:
            ret = EnAn_ProcessSchedule_AttendGoron(this, play, scheduleOutput);
            break;

        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            ret = EnAn_ProcessSchedule_GiveLunchToGranny(this, play, scheduleOutput);
            break;

        case ANJU_SCH_RANCH:
            ret = EnAn_ProcessSchedule_Ranch(this, play, scheduleOutput);
            break;

        case ANJU_SCH_WAITING_FOR_KAFEI:
        case ANJU_SCH_TALKING_WITH_MOM:
            ret = EnAn_ProcessSchedule_StaffRoom(this, play, scheduleOutput);
            break;

        case ANJU_SCH_LAUNDRY_POOL_SIT:
        case ANJU_SCH_COOKING:
        case ANJU_SCH_RECEPTIONIST_IDLE:
        case ANJU_SCH_WAITING_CLOSING_TIME:
        case ANJU_SCH_MIDNIGHT_MEETING:
            ret = EnAn_ProcessSchedule_80B56880(this, play, scheduleOutput);
            break;

        case ANJU_SCH_SWEEPING:
            ret = EnAn_ProcessSchedule_Sweeping(this, play, scheduleOutput);
            break;

        case ANJU_SCH_WITH_KAFEI:
            ret = EnAn_ProcessSchedule_WithKafei(this, play, scheduleOutput);
            break;

        case ANJU_SCH_DOOR_26:
        case ANJU_SCH_DOOR_27:
        case ANJU_SCH_DOOR_28:
        case ANJU_SCH_DOOR_29:
        case ANJU_SCH_DOOR_30:
        case ANJU_SCH_DOOR_31:
        case ANJU_SCH_DOOR_32:
        case ANJU_SCH_DOOR_33:
        case ANJU_SCH_DOOR_34:
        case ANJU_SCH_DOOR_35:
        case ANJU_SCH_DOOR_36:
        case ANJU_SCH_DOOR_37:
        case ANJU_SCH_DOOR_38:
        case ANJU_SCH_DOOR_39:
            ret = EnAn_ProcessSchedule_Door(this, play, scheduleOutput);
            break;

        case ANJU_SCH_WALKING_40:
        case ANJU_SCH_WALKING_42:
        case ANJU_SCH_WALKING_43:
        case ANJU_SCH_WALKING_44:
        case ANJU_SCH_WALKING_45:
        case ANJU_SCH_WALKING_46:
        case ANJU_SCH_WALKING_47:
        case ANJU_SCH_WALKING_48:
        case ANJU_SCH_WALKING_49:
        case ANJU_SCH_WALKING_50:
        case ANJU_SCH_WALKING_51:
        case ANJU_SCH_WALKING_52:
        case ANJU_SCH_WALKING_53:
        case ANJU_SCH_WALKING_54:
        case ANJU_SCH_WALKING_55:
        case ANJU_SCH_WALKING_56:
        case ANJU_SCH_WALKING_57:
        case ANJU_SCH_WALKING_58:
        case ANJU_SCH_WALKING_59:
        case ANJU_SCH_WALKING_60:
        case ANJU_SCH_WALKING_61:
        case ANJU_SCH_WALKING_62:
        case ANJU_SCH_WALKING_63:
            ret = EnAn_ProcessSchedule_Walking(this, play, scheduleOutput);
            break;

        default:
            ret = false;
            break;
    }

    return ret;
}

/* Start of HandleShedule functions */

// RotateTowardsLookAtActor?
s32 EnAn_HandleSch_InteractActor(EnAn* this, PlayState* play) {
    Vec3f lookAtActorPos;
    Vec3f pos;

    if ((this->lookAtActor != NULL) && (this->lookAtActor->update != NULL)) {
        Math_Vec3f_Copy(&lookAtActorPos, &this->lookAtActor->world.pos);
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&pos, &lookAtActorPos);
    }

    return true;
}

s32 EnAn_HandleSch_Door(EnAn* this, PlayState* play) {
    EnDoor* door = EnAn_FindDoor(play, this->scheduleResult);
    Vec3f sp38;
    f32 distance;
    s32 pad;

    if (!SubS_InCsMode(play) && (this->timePathTimeSpeed != 0)) {
        if ((door != NULL) && (door->knobDoor.dyna.actor.update != NULL)) {
            // Tell the door actor to be open while passing through it and which orientation
            if ((this->var1.doorTimeProgress / (f32)this->doorTimeTotalDiff) <= 0.9f) {
                door->openTimer = this->doorOpenTimer;
            } else {
                door->openTimer = 0;
            }
        }

        this->var1.doorTimeProgress = CLAMP(this->var1.doorTimeProgress, 0, this->doorTimeTotalDiff);
        distance = Math_Vec3f_DistXZ(&this->doorEntrancePos, &this->doorExitPos) / this->doorTimeTotalDiff;

        sp38.x = 0.0f;
        sp38.y = 0.0f;
        sp38.z = this->var1.doorTimeProgress * distance;

        Lib_Vec3f_TranslateAndRotateY(&this->doorEntrancePos, this->actor.world.rot.y, &sp38, &this->actor.world.pos);

        this->var1.doorTimeProgress += this->timePathTimeSpeed;
        if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_PIRATE_WALK);
        }
    }

    return 0;
}

s32 EnAn_HandleSch_FollowTimePath(EnAn* this, PlayState* play) {
    f32 knots[265];
    Vec3f worldPos;
    Vec3f sp64;
    Vec3f sp58;
    s32 timePathElapsedTime;
    s32 timePathWaypoint;
    s32 pad;

    timePathWaypoint = 0;
    timePathElapsedTime = 0;
    SubS_TimePathing_FillKnots(knots, SUBS_TIME_PATHING_ORDER, this->timePath->count + SUBS_TIME_PATHING_ORDER);

    if (!(this->stateFlags & ENAN_STATE_8)) {
        sp58 = gZeroVec3f;
        SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &sp58, this->timePathTimeSpeed);
        SubS_TimePathing_ComputeInitialY(play, this->timePath, this->timePathWaypoint, &sp58);
        this->actor.world.pos.y = sp58.y;
        this->stateFlags |= ENAN_STATE_8;
    } else {
        sp58 = this->timePathTargetPos;
    }

    this->actor.world.pos.x = sp58.x;
    this->actor.world.pos.z = sp58.z;

    if (SubS_InCsMode(play)) {
        timePathElapsedTime = this->timePathElapsedTime;
        timePathWaypoint = this->timePathWaypoint;
        sp58 = this->actor.world.pos;
    }
    this->timePathTargetPos = gZeroVec3f;

    if (SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &this->timePathTargetPos, this->timePathTimeSpeed)) {
        this->stateFlags |= ENAN_STATE_REACHED_PATH_END;
    } else {
        worldPos = this->actor.world.pos;
        sp64 = this->timePathTargetPos;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&worldPos, &sp64);
    }

    if (SubS_InCsMode(play)) {
        this->timePathElapsedTime = timePathElapsedTime;
        this->timePathWaypoint = timePathWaypoint;
        this->timePathTargetPos = sp58;
    } else if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_PIRATE_WALK);
    }

    return 0;
}

s32 EnAn_HandleSch_80B572D4(EnAn* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_MIDNIGHT_MEETING:
            if (func_80B55F8C(play) && EnAn_IsFacingAndNearPlayer(this)) {
                this->stateFlags |= ENAN_STATE_20;
            } else {
                this->stateFlags &= ~ENAN_STATE_20;
            }
            break;

        case ANJU_SCH_WAITING_FOR_KAFEI:
            if (EnAn_IsFacingAndNearPlayer(this)) {
                this->stateFlags |= ENAN_STATE_20;
            } else {
                this->stateFlags &= ~ENAN_STATE_20;
            }
            break;

        case ANJU_SCH_RECEPTIONIST_IDLE:
        case ANJU_SCH_WAITING_CLOSING_TIME:
            if (EnAn_IsFacingAndNearPlayer(this)) {
                this->stateFlags |= ENAN_STATE_20;
            } else {
                this->stateFlags &= ~ENAN_STATE_20;
            }
            break;

        case ANJU_SCH_SWEEPING:
            if (Animation_OnFrame(&this->skelAnime, 6.0f) && (this->animIndex == ENAN_ANIM_BROOM_SWEEP)) {
                Actor_PlaySfx(&this->actor, NA_SE_EV_SWEEP);
            }
            break;
    }

    return 0;
}

s32 EnAn_HandleSch_LaundryPool(EnAn* this, PlayState* play) {
    s16 worldRot;
    s16 shapeRot;

    switch (this->var1.laundryPoolState) {
        case 0x0:
            this->actor.world.rot.y += 0x7FF8;
            this->var1.laundryPoolState++;
            break;

        case 0x1:
            worldRot = (this->actor.world.rot.y / 0xB6) * 0xB6;
            shapeRot = (this->actor.shape.rot.y / 0xB6) * 0xB6;
            if (worldRot == shapeRot) {
                Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
                EnAn_ChangeAnim(this, play, ENAN_ANIM_UMBRELLA_SIT);
                this->stateFlags |= ENAN_STATE_IGNORE_GRAVITY;
                this->var1.laundryPoolState++;
            }
            break;

        case 0x2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->var1.laundryPoolState++;
            }
            break;

        case 0x3:
            if (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x3000) {
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            } else {
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
            }
            break;

        case 0x4:
            SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            this->var1.laundryPoolState++;
            break;
    }

    return 0;
}

s32 EnAn_HandleSch_WaitingForKafei(EnAn* this, PlayState* play) {
    s32 yRot = this->actor.shape.rot.y;
    s16 yaw = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, yRot));

    if (yaw < 0x4000) {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    } else {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
    }

    if (EnAn_IsFacingAndNearPlayer(this)) {
        this->stateFlags |= ENAN_STATE_20;
    } else {
        this->stateFlags &= ~ENAN_STATE_20;
    }

    return 1;
}

s32 EnAn_HandleSch_WithKafei(EnAn* this, PlayState* play) {
    s16 yRot = BINANG_ADD(this->actor.shape.rot.y, 0x3000);
    s16 yaw = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, yRot));

    if (yaw < 0x3000) {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    } else {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
    }

    this->stateFlags &= ~ENAN_STATE_20;
    return 1;
}

/* End of HandleShedule functions */

void EnAn_HandleSchedule(EnAn* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
        case ANJU_SCH_ATTEND_GORON:
        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            EnAn_HandleSch_InteractActor(this, play);
            break;

        case ANJU_SCH_LAUNDRY_POOL_SIT:
            EnAn_HandleSch_LaundryPool(this, play);
            break;

        case ANJU_SCH_WAITING_FOR_KAFEI:
            EnAn_HandleSch_WaitingForKafei(this, play);
            break;

        case ANJU_SCH_WITH_KAFEI:
            EnAn_HandleSch_WithKafei(this, play);
            break;

        case ANJU_SCH_RANCH:
        case ANJU_SCH_COOKING:
        case ANJU_SCH_RECEPTIONIST_IDLE:
        case ANJU_SCH_WAITING_CLOSING_TIME:
        case ANJU_SCH_SWEEPING:
        case ANJU_SCH_TALKING_WITH_MOM:
            EnAn_HandleSch_80B572D4(this, play);
            break;

        case ANJU_SCH_MIDNIGHT_MEETING:
            EnAn_HandleSch_80B572D4(this, play);
            break;

        case ANJU_SCH_DOOR_26:
        case ANJU_SCH_DOOR_27:
        case ANJU_SCH_DOOR_28:
        case ANJU_SCH_DOOR_29:
        case ANJU_SCH_DOOR_30:
        case ANJU_SCH_DOOR_31:
        case ANJU_SCH_DOOR_32:
        case ANJU_SCH_DOOR_33:
        case ANJU_SCH_DOOR_34:
        case ANJU_SCH_DOOR_35:
        case ANJU_SCH_DOOR_36:
        case ANJU_SCH_DOOR_37:
        case ANJU_SCH_DOOR_38:
        case ANJU_SCH_DOOR_39:
            EnAn_HandleSch_Door(this, play);
            break;

        case ANJU_SCH_WALKING_40:
        case ANJU_SCH_WALKING_42:
        case ANJU_SCH_WALKING_43:
        case ANJU_SCH_WALKING_44:
        case ANJU_SCH_WALKING_45:
        case ANJU_SCH_WALKING_46:
        case ANJU_SCH_WALKING_47:
        case ANJU_SCH_WALKING_48:
        case ANJU_SCH_WALKING_49:
        case ANJU_SCH_WALKING_50:
        case ANJU_SCH_WALKING_51:
        case ANJU_SCH_WALKING_52:
        case ANJU_SCH_WALKING_53:
        case ANJU_SCH_WALKING_54:
        case ANJU_SCH_WALKING_55:
        case ANJU_SCH_WALKING_56:
        case ANJU_SCH_WALKING_57:
        case ANJU_SCH_WALKING_58:
        case ANJU_SCH_WALKING_59:
        case ANJU_SCH_WALKING_60:
        case ANJU_SCH_WALKING_61:
        case ANJU_SCH_WALKING_62:
        case ANJU_SCH_WALKING_63:
            EnAn_HandleSch_FollowTimePath(this, play);
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void EnAn_Initialize(EnAn* this, PlayState* play) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gAnju1Skel, NULL, this->jointTable, this->morphTable, ANJU1_LIMB_MAX);

    this->animIndex = ENAN_ANIM_NONE;
    EnAn_ChangeAnim(this, play, ENAN_ANIM_IDLE);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);

    if (this->actor.params & ENAN_8000) {
        this->unk_3C0 = true;
    }

    this->actor.draw = EnAn_Draw;
    Actor_SetScale(&this->actor, 0.01f);
    this->stateFlags = 0;
    this->scheduleResult = ANJU_SCH_NONE;

    this->actionFunc = EnAn_FollowSchedule;
    this->actionFunc(this, play);
}

void EnAn_FollowSchedule(EnAn* this, PlayState* play) {
    ScheduleOutput scheduleOutput;

    this->timePathTimeSpeed = R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset);

    if (!(this->actor.params & ENAN_8000) && !this->unk_3C0 && CHECK_WEEKEVENTREG(WEEKEVENTREG_51_40)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (this->unk_3C0) {
        scheduleOutput.result = ANJU_SCH_WITH_KAFEI;
        if (this->scheduleResult != ANJU_SCH_WITH_KAFEI) {
            EnAn_ProcessScheduleOutput(this, play, &scheduleOutput);
        }
    } else if (!Schedule_RunScript(play, sScheduleScript, &scheduleOutput) ||
               ((this->scheduleResult != scheduleOutput.result) &&
                !EnAn_ProcessScheduleOutput(this, play, &scheduleOutput))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        scheduleOutput.result = ANJU_SCH_NONE;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    }

    this->scheduleResult = scheduleOutput.result;
    this->lookAtActor = EnAn_FindLookAtActor(this, play);
    EnAn_HandleSchedule(this, play);
}

void EnAn_Talk(EnAn* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->msgEventScript, this->msgEventFunc, &this->msgScriptResumePos)) {
        // Message event script is done

        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

        this->stateFlags &= ~ENAN_STATE_20;
        this->stateFlags |= ENAN_STATE_200;
        this->unk_388 = 20;
        this->msgScriptResumePos = 0;
        this->actionFunc = EnAn_FollowSchedule;

        return;
    }

    if ((this->scheduleResult == ANJU_SCH_WAITING_FOR_KAFEI) || (this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) ||
        (this->scheduleResult == ANJU_SCH_RANCH) || (this->scheduleResult == ANJU_SCH_COOKING) ||
        (this->scheduleResult == ANJU_SCH_WITH_KAFEI)) {
        return;
    }

    if ((this->lookAtActor != NULL) && (this->lookAtActor->update != NULL)) {
        // Rotate towards actor
        s32 temp;
        Vec3f sp38;
        Vec3f sp2C;

        Math_Vec3f_Copy(&sp38, &this->lookAtActor->world.pos);
        Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
        temp = Math_Vec3f_Yaw(&sp2C, &sp38);

        Math_ApproachS(&this->actor.shape.rot.y, temp, 4, 0x2AA8);
    }
}

void EnAn_HandleCutscene(EnAn* this, PlayState* play) {
    s32 animIds[] = {
        /* 0 */ ENAN_ANIM_HOLDING_HANDS,
        /* 1 */ ENAN_ANIM_SITTING_IN_DISBELIEVE,
        /* 2 */ ENAN_ANIM_SITTING_RAISE_FACE,
        /* 3 */ ENAN_ANIM_25,
        /* 4 */ ENAN_ANIM_26,
        /* 5 */ ENAN_ANIM_28,
        /* 6 */ ENAN_ANIM_30,
        /* 7 */ ENAN_ANIM_32,
        /* 8 */ ENAN_ANIM_33,
        /* 9 */ ENAN_ANIM_HOLDING_HANDS,
    };
    s32 pad;

    //! FAKE
    if (0) {}

    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_557)) {
        s32 cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_557);
        u16 cueId = play->csCtx.actorCues[cueChannel]->id;

        if (this->cueId != (cueId & 0xFF)) {
            this->cueId = cueId;

            if (this->cueId == 3) {
                SET_WEEKEVENTREG(WEEKEVENTREG_87_02);
                this->drawMoonMask = true;
            }
            if (this->cueId == 9) {
                this->drawMoonMask = false;
            }

            EnAn_ChangeAnim(this, play, animIds[cueId]);
        }

        if ((this->animIndex == ENAN_ANIM_26) || (this->animIndex == ENAN_ANIM_28) ||
            (this->animIndex == ENAN_ANIM_30) || (this->animIndex == ENAN_ANIM_SITTING_RAISE_FACE)) {
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                EnAn_ChangeAnim(this, play, this->animIndex + 1);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
    }
}

#if DEBUG_PRINT
u8 weekEventRegCopy[100];
#endif

void EnAn_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnAn* this = THIS;
    s32 temp_v1;
    s32 temp_v0;

    if (play->sceneId != SCENE_YADOYA) {
        this->actor.params &= (s16)~ENAN_8000;
    }

    temp_v1 = (this->actor.params & ENAN_8000) >> 0xF;
    temp_v0 = CHECK_WEEKEVENTREG(WEEKEVENTREG_51_40);

    if (((temp_v0 == 0) && (temp_v1 == 1)) || ((temp_v0 != 0) && (temp_v1 == 0))) {
        Actor_Kill(&this->actor);
        return;
    }

    if (temp_v1 == 0) {
        if (func_80B53A7C(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
            Actor_Kill(&this->actor);
            return;
        }
    }

    this->roomNum = -0x80;
    this->slotsInitialized = false;
    if (temp_v1 == 0) {
        this->actor.room = -1;
    }

    this->actionFunc = EnAn_Initialize;

#if DEBUG_PRINT
    Lib_MemCpy(weekEventRegCopy, gSaveContext.save.saveInfo.weekEventReg, sizeof(gSaveContext.save.saveInfo.weekEventReg));

    gSaveContext.save.day = 3;

    if (gSaveContext.save.time > CLOCK_TIME(5, 0)) {
        gSaveContext.save.time = CLOCK_TIME(4, 30);
    }

    SET_WEEKEVENTREG(WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES);
    SET_WEEKEVENTREG(WEEKEVENTREG_ESCAPED_SAKONS_HIDEOUT);
#endif
}

void EnAn_Destroy(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnAn_Update(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if (EnAn_InitializeObjectSlots(this, play)) {
        return;
    }

    if ((this->actionFunc != EnAn_Initialize) && !EnAn_CheckTalk(this, play) && func_80B552E4(this, play)) {
        EnAn_HandleCutscene(this, play);
        EnAn_UpdateSkel(this, play);
        EnAn_UpdateFace(this);
        return;
    }

    this->actionFunc(this, play);
    if (this->scheduleResult != ANJU_SCH_NONE) {
        EnAn_HandleDialogue(this, play);
        EnAn_UpdateSkel(this, play);
        EnAn_UpdateFace(this);
        func_80B554E8(this);
        SubS_Offer(&this->actor, play, this->unk_374, 30.0f, 0, this->stateFlags & SUBS_OFFER_MODE_MASK);

        if (!(this->stateFlags & ENAN_STATE_IGNORE_GRAVITY)) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
        }

        EnAn_UpdateCollider(this, play);
    }
}

Vec3f D_80B58ED4 = { 1000.0f, 0.0f, 0.0f };

void EnAn_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnAn* this = THIS;

    if (limbIndex == ANJU1_LIMB_HEAD) {
        Matrix_MultVec3f(&D_80B58ED4, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
        EnAn_DrawAccessory(this, play, ENAN_ACCESSORY_KAFEI_MASK);
    } else if (limbIndex == ANJU1_LIMB_RIGHT_HAND) {
        EnAn_DrawAccessory(this, play, ENAN_ACCESSORY_FOOD_TRAY);
        EnAn_DrawAccessory(this, play, ENAN_ACCESSORY_CHOPSTICKS);
        EnAn_DrawAccessory(this, play, ENAN_ACCESSORY_UMBRELLA);
        EnAn_DrawAccessory(this, play, ENAN_ACCESSORY_BROOM);
    } else if (limbIndex == ANJU1_LIMB_LEFT_HAND) {
        EnAn_DrawAccessory(this, play, ENAN_ACCESSORY_MOON_MASK);
    }
}

void EnAn_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnAn* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->stateFlags & ENAN_STATE_200)) {
        if (this->stateFlags & ENAN_STATE_80) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == ANJU1_LIMB_HEAD) {
        SubS_UpdateLimb(this->headRotZ + 0x4000, this->headRotY + this->actor.shape.rot.y + 0x4000,
                        &this->headComputedPos, &this->headComputedRot, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->headComputedPos.x, this->headComputedPos.y, this->headComputedPos.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->headComputedRot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->headComputedRot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->headComputedRot.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

#if DEBUG_PRINT
#define BOOLSTR(x) ((x) ? "true" : "false")

#define DEC_TIME_AUX(t) ((t) * (24 * 60) / 0x10000)
#define DEC_TIME(t) ((DEC_TIME_AUX(t) / 60) * 100 + (DEC_TIME_AUX(t) % 60))

void EnAn_PrintStruct(EnAn* this, PlayState* play, GfxPrint* printer) {
    s32 x = 31;
    s32 y = 3 + 22;
    s32 i;
    uintptr_t actionFuncReloc;

    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    GfxPrint_SetPos(printer, 28, 1);
    GfxPrint_Printf(printer, "gTime:%X", gSaveContext.save.time);

    GfxPrint_SetPos(printer, 28, 2);
    GfxPrint_Printf(printer, "gTime:%i:%i", DEC_TIME_AUX(gSaveContext.save.time) / 60, DEC_TIME_AUX(gSaveContext.save.time) % 60);

    //GfxPrint_SetPos(printer, x - 7, ++y);
    //actionFuncReloc = (uintptr_t)this->actionFunc - (uintptr_t)EnAn_InitializeObjectSlots + SEGMENT_START(ovl_En_An);
    //GfxPrint_Printf(printer, "actionFunc:%X", actionFuncReloc & 0x0000FFFF);

    GfxPrint_SetPos(printer, x-5, ++y);
    GfxPrint_Printf(printer, "schedule:%d", this->scheduleResult);

    //GfxPrint_SetPos(printer, x-3, ++y);
    //GfxPrint_Printf(printer, "textId:%X", this->prevTextId);

    GfxPrint_SetPos(printer, x-0, ++y);
    GfxPrint_Printf(printer, "cue:%d", this->cueId);

    //GfxPrint_SetPos(printer, x-2, ++y);
    //GfxPrint_Printf(printer, "! 374:%f", this->unk_374);

    //GfxPrint_SetPos(printer, x-6, ++y);
    //GfxPrint_Printf(printer, "savedFace:%d", this->savedFaceIndex);

    //GfxPrint_SetPos(printer, x-1, ++y);
    //GfxPrint_Printf(printer, "face:%d", this->faceIndex);

    //GfxPrint_SetPos(printer, x-5, ++y);
    //GfxPrint_Printf(printer, "eyeTimer:%d", this->eyeTimer);

    //GfxPrint_SetPos(printer, x-0, ++y);
    //GfxPrint_Printf(printer, "eye:%d", this->eyeTexIndex);

    //GfxPrint_SetPos(printer, x-2, ++y);
    //GfxPrint_Printf(printer, "mouth:%d", this->mouthTexIndex);

    GfxPrint_SetPos(printer, x-1, ++y);
    GfxPrint_Printf(printer, "anim:%d", this->animIndex);

    //GfxPrint_SetPos(printer, x-2, ++y);
    //GfxPrint_Printf(printer, "! 3C0:%s", BOOLSTR(this->unk_3C0));

    y = 0;
    {
        static const char* const subsFlags[8] = {
            "SUBS_OFFER_MODE_NONE",
            "SUBS_OFFER_MODE_GET_ITEM",
            "SUBS_OFFER_MODE_NEARBY",
            "SUBS_OFFER_MODE_ONSCREEN",
            "SUBS_OFFER_MODE_AUTO",
            "SUBS_OFFER_MODE_AUTO_TARGETED",
            "SUBS_OFFER_MODE_AUTO_NEARBY_ONSCREEN",
            "SUBS_OFFER_MODE_INVALID",
        };
        s32 index = this->stateFlags & SUBS_OFFER_MODE_MASK;

        GfxPrint_SetPos(printer, 1, ++y);
        GfxPrint_Printf(printer, "SUBS_%s", &subsFlags[index][16]);
    }

    for (i = 3; i < 16; i++) {
        static const char* const flagsMap[16] = {
            "ENAN_STATE_PLACEHOLDER_1",
            "ENAN_STATE_PLACEHOLDER_2",
            "ENAN_STATE_PLACEHOLDER_4",
            "ENAN_STATE_8",
            "ENAN_STATE_REACHED_PATH_END",
            "ENAN_STATE_20",
            "ENAN_STATE_IGNORE_GRAVITY",
            "ENAN_STATE_80",
            "ENAN_STATE_UPDATE_EYES",
            "ENAN_STATE_200",
            "ENAN_STATE_TALKING",
            "ENAN_STATE_DRAW_TRAY",
            "ENAN_STATE_DRAW_UMBRELLA",
            "ENAN_STATE_DRAW_BROOM",
            "ENAN_STATE_DRAW_KAFEI_MASK",
            "ENAN_STATE_DRAW_CHOPSTICKS",
        };

        if (this->stateFlags & (1 << i)) {
            GfxPrint_SetPos(printer, 1, ++y);
            GfxPrint_Printf(printer, "%s", &flagsMap[i][11]);
        }
    }

    y = 20;
    x = 3;

    GfxPrint_SetPos(printer, x - 2, ++y);
    GfxPrint_Printf(printer, "weekEvent");

    for (i = 0; i < ARRAY_COUNT(weekEventRegCopy); i++){
        if (weekEventRegCopy[i] != gSaveContext.save.saveInfo.weekEventReg[i]) {
            u8 copy = weekEventRegCopy[i];
            u8 real = gSaveContext.save.saveInfo.weekEventReg[i];
            u8 diff = copy ^ real;
            s32 j;

            for (j = 0; j < 8; j++) {
                u8 mask = (1 << j);

                if (diff & mask) {
                    if (real & mask) {
                        GfxPrint_SetPos(printer, x, ++y);
                        GfxPrint_Printf(printer, "SET [%i] & %X", i, mask);
                    } else {

                    }
                }
            }
        }
    }
}

void EnAn_DrawStruct(EnAn* this, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    GfxPrint printer;
    Gfx* gfxRef;
    Gfx* gfx;

    OPEN_DISPS(gfxCtx);

    Gfx_SetupDL28_Opa(gfxCtx);

    GfxPrint_Init(&printer);

    gfxRef = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(gfxRef);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    GfxPrint_Open(&printer, gfx);

    EnAn_PrintStruct(this, play, &printer);

    gfx = GfxPrint_Close(&printer);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(gfxRef, gfx);
    POLY_OPA_DISP = gfx;

    GfxPrint_Destroy(&printer);

    CLOSE_DISPS(gfxCtx);
}
#endif

static TexturePtr sMouthTextures[ENAN_MOUTH_MAX] = {
    gAnju1Mouth00E6E0Tex, // ENAN_MOUTH_0
    gAnju1MouthHappyTex,  // ENAN_MOUTH_HAPPY
    gAnju1Mouth0101A0Tex, // ENAN_MOUTH_2
};

static TexturePtr sEyeTextures[ENAN_EYES_MAX] = {
    gAnju1EyeOpenTex,   // ENAN_EYES_OPEN
    gAnju1EyeHalfTex,   // ENAN_EYES_HALF1
    gAnju1EyeClosedTex, // ENAN_EYES_CLOSED
    gAnju1EyeHalfTex,   // ENAN_EYES_HALF2
    gAnju1Eye00FDA0Tex, // ENAN_EYES_4
    gAnju1EyeSadTex,    // ENAN_EYES_SAD
    gAnju1EyeAngryTex,  // ENAN_EYES_ANGRY
};

void EnAn_Draw(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if ((this->scheduleResult != ANJU_SCH_NONE) || this->forceDraw) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTexIndex]));

        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, NULL, EnAn_PostLimbDraw, EnAn_TransformLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }

#if DEBUG_PRINT
    EnAn_DrawStruct(this, play);
#endif
}
