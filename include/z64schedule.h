#ifndef _Z64SCHEDULE_H_
#define _Z64SCHEDULE_H_

#include "ultra64.h"

/*
  Schedule is a subsystem that acts as a way to make decisions based on the
  time and scene (and a limited selection of items). It is utilized by writing
  a script that is encoded into bytecode and ran, returning the result in a
  struct. The returned result can be a value or a encoded time value.

  The scripts contain 2 kinds of instructions:
  - Checks with jumps (relative offsets, either 1-byte offsets (short, *_S),
                       or 2-byte offsets (long, *_L))
  - Returns

  Scripts are stored as u8[]. They are built using the macros are the bottom of
  this file. The scheduledis.py script can be used to convert any scripts in
  actor data into the macros.
*/

// Macro to convert the time format used in the save struct into the format used in Schedule
#define SCHEDULE_CONVERT_TIME(time) ((time) - 0x10000 / 360 * 90)
#define SCHEDULE_TIME_NOW SCHEDULE_CONVERT_TIME(gSaveContext.time)

typedef enum {
    /* 00 */ SCHEDULE_CMD_ID_FLAG_CHECK_S,       // Checks if a weekEventReg flag is set and jumps if so, short range jump
    /* 01 */ SCHEDULE_CMD_ID_FLAG_CHECK_L,       // Checks if a weekEventReg flag is set and jumps if so, long range jump
    /* 02 */ SCHEDULE_CMD_ID_TIME_RANGE_CHECK_S, // Checks if the current time is within the range of the two provided times and jumps if so, short range jump
    /* 03 */ SCHEDULE_CMD_ID_TIME_RANGE_CHECK_L, // Checks if the current time is within the range of the two provided times and jumps if so, long range jump
    /* 04 */ SCHEDULE_CMD_ID_RETURN_L,           // Returns 2-byte value (Note: bugged as the return value size is only 1 byte in the struct)
    /* 05 */ SCHEDULE_CMD_ID_END,                // Ends script without returning anything
    /* 06 */ SCHEDULE_CMD_ID_RETURN_EMPTY,       // Ends script and indicates return without changing existing value
    /* 07 */ SCHEDULE_CMD_ID_NOP,                // No-Op
    /* 08 */ SCHEDULE_CMD_ID_ITEM_CHECK_S,       // Special check based on items or masks and jumps if check passes, short range jump
    /* 09 */ SCHEDULE_CMD_ID_RETURN_S,           // Returns byte value
    /* 10 */ SCHEDULE_CMD_ID_SCENE_CHECK_S,      // Checks if the current scene is SceneNum and jumps if not, short range jump
    /* 11 */ SCHEDULE_CMD_ID_SCENE_CHECK_L,      // Checks if the current scene is SceneNum and jumps if not, long range jump
    /* 12 */ SCHEDULE_CMD_ID_DAY_CHECK_S,        // Checks if the current day is Day and jumps if not, short range jump
    /* 13 */ SCHEDULE_CMD_ID_DAY_CHECK_L,        // Checks if the current day is Day and jumps if not, long range jump
    /* 14 */ SCHEDULE_CMD_ID_RETURN_TIME,        // Returns 2 time values
    /* 15 */ SCHEDULE_CMD_ID_TIME_CHECK_S,       // Jumps if the current time is less than the command time, short range jump
    /* 16 */ SCHEDULE_CMD_ID_TIME_CHECK_L,       // Jumps if the current time is less than the command time, long range jump
    /* 17 */ SCHEDULE_CMD_ID_JUMP_S,             // Always jump, short range jump
    /* 18 */ SCHEDULE_CMD_ID_JUMP_L,             // Always jump, long range jump
} ScheduleCommandID;

typedef enum {
    /* 0 */ SCHEDULE_ITEM_CHECK_ROOM_KEY,
    /* 1 */ SCHEDULE_ITEM_CHECK_LETTER_TO_KAFEI,
    /* 2 */ SCHEDULE_ITEM_CHECK_MASK_ROMANI,
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

#define SCHEDULE_CMD_FLAG_CHECK_S(index, mask, offset) \
    SCHEDULE_CMD_ID_FLAG_CHECK_S, (index), (mask), (offset)

#define SCHEDULE_CMD_FLAG_CHECK_L(index, mask, offset) \
    SCHEDULE_CMD_ID_FLAG_CHECK_L, (index), (mask), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_TIME_RANGE_CHECK_S(startHr, startMin, endHr, endMin, offset) \
    SCHEDULE_CMD_ID_TIME_RANGE_CHECK_S, (startHr), (startMin), (endHr), (endMin), (offset)

#define SCHEDULE_CMD_TIME_RANGE_CHECK_L(startHr, startMin, endHr, endMin, offset) \
    SCHEDULE_CMD_ID_TIME_RANGE_CHECK_L, (startHr), (startMin), (endHr), (endMin), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_RETURN_L(ret) \
    SCHEDULE_CMD_ID_RETURN_L, SCHEDULE_PACK_S16(ret)

#define SCHEDULE_CMD_END() \
    SCHEDULE_CMD_ID_END

#define SCHEDULE_CMD_RETURN_EMPTY() \
    SCHEDULE_CMD_ID_RETURN_EMPTY,

#define SCHEDULE_CMD_NOP(unk0, unk1, unk2) \
    SCHEDULE_CMD_ID_NOP, (unk0), (unk1), (unk2)

#define SCHEDULE_CMD_ITEM_CHECK_S(which, offset) \
    SCHEDULE_CMD_ID_ITEM_CHECK_S, (which), (offset)

#define SCHEDULE_CMD_RETURN_S(ret) \
    SCHEDULE_CMD_ID_RETURN_S, (ret)

#define SCHEDULE_CMD_SCENE_CHECK_S(scene, offset) \
    SCHEDULE_CMD_ID_SCENE_CHECK_S, SCHEDULE_PACK_S16(scene), (offset)

#define SCHEDULE_CMD_SCENE_CHECK_L(scene, offset) \
    SCHEDULE_CMD_ID_SCENE_CHECK_L, SCHEDULE_PACK_S16(scene), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_DAY_CHECK_S(day, offset) \
    SCHEDULE_CMD_ID_DAY_CHECK_S, SCHEDULE_PACK_S16(day), (offset)

#define SCHEDULE_CMD_DAY_CHECK_L(day, offset) \
    SCHEDULE_CMD_ID_DAY_CHECK_L, SCHEDULE_PACK_S16(day), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_RETURN_TIME(time0Hr, time0Min, time1Hr, time1Min, ret) \
    SCHEDULE_CMD_ID_RETURN_TIME, (time0Hr), (time0Min), (time1Hr), (time1Min), (ret)

#define SCHEDULE_CMD_TIME_CHECK_S(timeHr, timeMin, offset) \
    SCHEDULE_CMD_ID_TIME_CHECK_S, (timeHr), (timeMin), (offset)

#define SCHEDULE_CMD_TIME_CHECK_L(timeHr, timeMin, offset) \
    SCHEDULE_CMD_ID_TIME_CHECK_L, (timeHr), (timeMin), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_JUMP_S(offset) \
    SCHEDULE_CMD_ID_JUMP_S, (offset)

#define SCHEDULE_CMD_JUMP_L(offset) \
    SCHEDULE_CMD_ID_JUMP_L, SCHEDULE_PACK_S16(offset)

#endif
