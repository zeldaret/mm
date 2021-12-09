#ifndef _Z64SCHEDULE_H_
#define _Z64SCHEDULE_H_

#include "ultra64.h"

// TODO use
#define SCHEDULE_CONVERT_TIME(time) ((time) - 0x10000 / 360 * 90)

typedef enum {
    /* 00 */ SCH_CMD_ID_FLAG_CHECK_S,
    /* 01 */ SCH_CMD_ID_FLAG_CHECK_L,
    /* 02 */ SCH_CMD_ID_TIME_RANGE_CHECK_S,
    /* 03 */ SCH_CMD_ID_TIME_RANGE_CHECK_L,
    /* 04 */ SCH_CMD_ID_RETURN_L,
    /* 05 */ SCH_CMD_ID_END,
    /* 06 */ SCH_CMD_ID_RETURN_EMPTY,
    /* 07 */ SCH_CMD_ID_NOP,
    /* 08 */ SCH_CMD_ID_ITEM_CHECK_S,
    /* 09 */ SCH_CMD_ID_RETURN_S,
    /* 10 */ SCH_CMD_ID_SCENE_CHECK_S,
    /* 11 */ SCH_CMD_ID_SCENE_CHECK_L,
    /* 12 */ SCH_CMD_ID_DAY_CHECK_S,
    /* 13 */ SCH_CMD_ID_DAY_CHECK_L,
    /* 14 */ SCH_CMD_ID_RETURN_TIME,
    /* 15 */ SCH_CMD_ID_TIME_CHECK_S,
    /* 16 */ SCH_CMD_ID_TIME_CHECK_L,
    /* 17 */ SCH_CMD_ID_JUMP_S,
    /* 18 */ SCH_CMD_ID_JUMP_L,
} ScheduleCommandID;

typedef enum {
    /* 0 */ SCH_ITEM_CHECK_ROOM_KEY,
    /* 1 */ SCH_ITEM_CHECK_LETTER_KAFEI,
    /* 2 */ SCH_ITEM_CHECK_MASK_ROMANI,
} ScheduleItemCheck;

typedef struct {
    /* 0x0 */ u8 result;
    /* 0x4 */ s32 time0;
    /* 0x8 */ s32 time1;
    /* 0xC */ s32 hasResult;
} ScheduleResult; // size = 0x10

typedef struct {
    /* 0x0 */ u8 cmd;
} ScheduleCmdBase; // size = 0x1

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 flagByte;
    /* 0x2 */ u8 flagMask;
    /* 0x3 */ s8 offset;
} ScheduleCmdFlagCheckS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 flagByte;
    /* 0x2 */ u8 flagMask;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdFlagCheckL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 startHr;
    /* 0x2 */ u8 startMin;
    /* 0x3 */ u8 endHr;
    /* 0x4 */ u8 endMin;
    /* 0x5 */ s8 offset;
} ScheduleCmdTimeRangeCheckS; // size = 0x6

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 startHr;
    /* 0x2 */ u8 startMin;
    /* 0x3 */ u8 endHr;
    /* 0x4 */ u8 endMin;
    /* 0x5 */ u8 offsetH;
    /* 0x6 */ u8 offsetL;
} ScheduleCmdTimeRangeCheckL; // size = 0x7

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 retH;
    /* 0x2 */ u8 retL;
} ScheduleCmdReturnL; // size = 0x3

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
} ScheduleCmdNop; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 which;
    /* 0x2 */ s8 offset;
} ScheduleCmdItemCheckS; // size = 0x3

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 res; // TODO rename
} ScheduleCmdReturnS; // size = 0x2

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 sceneH;
    /* 0x2 */ u8 sceneL;
    /* 0x3 */ s8 offset;
} ScheduleCmdSceneCheckS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 sceneH;
    /* 0x2 */ u8 sceneL;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdSceneCheckL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 dayH;
    /* 0x2 */ u8 dayL;
    /* 0x3 */ s8 offset;
} ScheduleCmdDayCheckS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 dayH;
    /* 0x2 */ u8 dayL;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdDayCheckL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 time0Hr;
    /* 0x2 */ u8 time0Min;
    /* 0x3 */ u8 time1Hr;
    /* 0x4 */ u8 time1Min;
    /* 0x5 */ u8 res; // TODO rename? (updadte macros too)
} ScheduleCmdReturnTime; // size = 0x6

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 timeHr;
    /* 0x2 */ u8 timeMin;
    /* 0x3 */ s8 offset;
} ScheduleCmdTimeCheckS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 timeHr;
    /* 0x2 */ u8 timeMin;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdTimeCheckL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ s8 offset;
} ScheduleCmdJumpS; // size = 0x2

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 offsetH;
    /* 0x2 */ u8 offsetL;
} ScheduleCmdJumpL; // size = 0x3

#define SCHEDULE_PACK_S16(val) \
    ((val) >> 8) & 0xFF, (val) & 0xFF

// TODO static?
#define SCHEDULE_START(name) \
    static u8 name[] = {

#define SCHEDULE_CMD_FLAG_CHECK_S(index, mask, offset) \
    SCH_CMD_ID_FLAG_CHECK_S, (index), (mask), (offset)

#define SCHEDULE_CMD_FLAG_CHECK_L(index, mask, offset) \
    SCH_CMD_ID_FLAG_CHECK_L, (index), (mask), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_TIME_RANGE_CHECK_S(startHr, startMin, endHr, endMin, offset) \
    SCH_CMD_ID_TIME_RANGE_CHECK_S, (startHr), (startMin), (endHr), (endMin), (offset)

#define SCHEDULE_CMD_TIME_RANGE_CHECK_L(startHr, startMin, endHr, endMin, offset) \
    SCH_CMD_ID_TIME_RANGE_CHECK_L, (startHr), (startMin), (endHr), (endMin), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_RETURN_L(ret) \
    SCH_CMD_ID_RETURN_L, SCHEDULE_PACK_S16(ret)

#define SCHEDULE_CMD_END() \
    SCH_CMD_ID_END

#define SCHEDULE_CMD_RETURN_EMPTY() \
    SCH_CMD_ID_RETURN_EMPTY,

#define SCHEDULE_CMD_NOP(unk0, unk1, unk2) \
    SCH_CMD_ID_NOP, (unk0), (unk1), (unk2)

#define SCHEDULE_CMD_ITEM_CHECK_S(which, offset) \
    SCH_CMD_ID_ITEM_CHECK_S, (which), (offset)

#define SCHEDULE_CMD_RETURN_S(ret) \
    SCH_CMD_ID_RETURN_S, (ret)

#define SCHEDULE_CMD_SCENE_CHECK_S(scene, offset) \
    SCH_CMD_ID_SCENE_CHECK_S, SCHEDULE_PACK_S16(scene), (offset)

#define SCHEDULE_CMD_SCENE_CHECK_L(scene, offset) \
    SCH_CMD_ID_SCENE_CHECK_L, SCHEDULE_PACK_S16(scene), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_DAY_CHECK_S(day, offset) \
    SCH_CMD_ID_DAY_CHECK_S, SCHEDULE_PACK_S16(day), (offset)

#define SCHEDULE_CMD_DAY_CHECK_L(day, offset) \
    SCH_CMD_ID_DAY_CHECK_L, SCHEDULE_PACK_S16(day), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_RETURN_TIME(time0Hr, time0Min, time1Hr, time1Min, ret) \
    SCH_CMD_ID_RETURN_TIME, (time0Hr), (time0Min), (time1Hr), (time1Min), (ret)

#define SCHEDULE_CMD_TIME_CHECK_S(timeHr, timeMin, offset) \
    SCH_CMD_ID_TIME_CHECK_S, (timeHr), (timeMin), (offset)

#define SCHEDULE_CMD_TIME_CHECK_L(timeHr, timeMin, offset) \
    SCH_CMD_ID_TIME_CHECK_L, (timeHr), (timeMin), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_JUMP_S(offset) \
    SCH_CMD_ID_JUMP_S, (offset)

#define SCHEDULE_CMD_JUMP_L(offset) \
    SCH_CMD_ID_JUMP_L, SCHEDULE_PACK_S16(offset)

#define SCHEDULE_END \
    };

#endif
