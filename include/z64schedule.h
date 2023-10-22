#ifndef Z64SCHEDULE_H
#define Z64SCHEDULE_H

#include "ultra64.h"

/**
 *   Schedule is a subsystem that acts as a way to make decisions based on the
 * time and scene (and a limited selection of items). It is utilized by writing
 * a script that is encoded into bytecode and run, returning the result in a
 * struct. The returned result can be a value or a encoded time value.
 *
 * The scripts contain 2 kinds of instructions:
 * - Checks with branches (relative offsets, either 1-byte offsets (short, *_S),
 *                         or 2-byte offsets (long, *_L))
 * - Returns
 *
 * Scripts are stored as u8[]. They are built using the macros are the bottom of
 * this file. The scheduledis.py script can be used to convert any scripts in
 * actor data into the macros.
 */

/**
 * Actors that use this system generally create 3 functions to interact with it.
 *
 * - FollowSchedule: The action function an actor sets to follow the schedule.
 * - ProcessScheduleOutput: Holds the logic of processing the output received by running the schedule script, called by FollowSchedule
 * - HandleSchedule: Holds the actual logic of how to actually follow the schedule based on the processed output, called by FollowSchedule
 */

// Macro to convert the time format used in the save struct into the format used in Schedule
#define SCHEDULE_CONVERT_TIME(time) ((s32)((time) - 0x10000 / 360 * 90))

#define SCHEDULE_TIME(hour, minute) SCHEDULE_CONVERT_TIME((((hour)*60.0f) + (minute)) * (0x10000 / 60 / 24.0f))

#define SCHEDULE_TIME_NOW SCHEDULE_CONVERT_TIME(gSaveContext.save.time)

typedef enum ScheduleCommandId {
    /* 0x00 */ SCHEDULE_CMD_ID_CHECK_FLAG_S,         // Checks if a weekEventReg flag is set and branches if so, short range branch
    /* 0x01 */ SCHEDULE_CMD_ID_CHECK_FLAG_L,         // Checks if a weekEventReg flag is set and branches if so, long range branch
    /* 0x02 */ SCHEDULE_CMD_ID_CHECK_TIME_RANGE_S,   // Checks if the current time is within the range of the two provided times and branches if so, short range branch
    /* 0x03 */ SCHEDULE_CMD_ID_CHECK_TIME_RANGE_L,   // Checks if the current time is within the range of the two provided times and branches if so, long range branch
    /* 0x04 */ SCHEDULE_CMD_ID_RET_VAL_L,            // Ends script and returns 2-byte value (Note: bugged as the return value size is only 1 byte in the struct)
    /* 0x05 */ SCHEDULE_CMD_ID_RET_NONE,             // Ends script without returning anything
    /* 0x06 */ SCHEDULE_CMD_ID_RET_EMPTY,            // Ends script and indicates return without changing existing value
    /* 0x07 */ SCHEDULE_CMD_ID_NOP,                  // No-Op
    /* 0x08 */ SCHEDULE_CMD_ID_CHECK_MISC_S,         // Special check based on items or masks and branches if check passes, short range branch
    /* 0x09 */ SCHEDULE_CMD_ID_RET_VAL_S,            // Ends script and returns byte value
    /* 0x0A */ SCHEDULE_CMD_ID_CHECK_NOT_IN_SCENE_S, // Checks if the current scene is not SceneId and branches if so, short range branch
    /* 0x0B */ SCHEDULE_CMD_ID_CHECK_NOT_IN_SCENE_L, // Checks if the current scene is not SceneId and branches if so, long range branch
    /* 0x0C */ SCHEDULE_CMD_ID_CHECK_NOT_IN_DAY_S,   // Checks if the current day is not Day and branches if so, short range branch
    /* 0x0D */ SCHEDULE_CMD_ID_CHECK_NOT_IN_DAY_L,   // Checks if the current day is not Day and branches if so, long range branch
    /* 0x0E */ SCHEDULE_CMD_ID_RET_TIME,             // Returns 2 time values
    /* 0x0F */ SCHEDULE_CMD_ID_CHECK_BEFORE_TIME_S,  // Branches if the current time is less than the command time, short range branch
    /* 0x10 */ SCHEDULE_CMD_ID_CHECK_BEFORE_TIME_L,  // Branches if the current time is less than the command time, long range branch
    /* 0x11 */ SCHEDULE_CMD_ID_BRANCH_S,             // Always branch, short range branch
    /* 0x12 */ SCHEDULE_CMD_ID_BRANCH_L              // Always branch, long range branch
} ScheduleCommandId;

typedef enum {
    /* 0 */ SCHEDULE_CHECK_MISC_ROOM_KEY,
    /* 1 */ SCHEDULE_CHECK_MISC_LETTER_TO_KAFEI,
    /* 2 */ SCHEDULE_CHECK_MISC_MASK_ROMANI
} ScheduleCheckMisc;

typedef struct {
    /* 0x0 */ u8 result;
    /* 0x4 */ s32 time0;
    /* 0x8 */ s32 time1;
    /* 0xC */ s32 hasResult;
} ScheduleOutput; // size = 0x10

typedef struct {
    /* 0x0 */ u8 cmd;
} ScheduleCmdBase; // size = 0x1

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 flagByte;
    /* 0x2 */ u8 flagMask;
    /* 0x3 */ s8 offset;
} ScheduleCmdCheckFlagS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 flagByte;
    /* 0x2 */ u8 flagMask;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdCheckFlagL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 startHr;
    /* 0x2 */ u8 startMin;
    /* 0x3 */ u8 endHr;
    /* 0x4 */ u8 endMin;
    /* 0x5 */ s8 offset;
} ScheduleCmdCheckTimeRangeS; // size = 0x6

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 startHr;
    /* 0x2 */ u8 startMin;
    /* 0x3 */ u8 endHr;
    /* 0x4 */ u8 endMin;
    /* 0x5 */ u8 offsetH;
    /* 0x6 */ u8 offsetL;
} ScheduleCmdCheckTimeRangeL; // size = 0x7

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 retH;
    /* 0x2 */ u8 retL;
} ScheduleCmdReturnValueL; // size = 0x3

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
} ScheduleCmdCheckMiscS; // size = 0x3

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 result;
} ScheduleCmdReturnValueS; // size = 0x2

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 sceneIdH;
    /* 0x2 */ u8 sceneIdL;
    /* 0x3 */ s8 offset;
} ScheduleCmdCheckNotInSceneS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 sceneIdH;
    /* 0x2 */ u8 sceneIdL;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdCheckNotInSceneL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 dayH;
    /* 0x2 */ u8 dayL;
    /* 0x3 */ s8 offset;
} ScheduleCmdCheckNotInDayS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 dayH;
    /* 0x2 */ u8 dayL;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdCheckNotInDayL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 time0Hr;
    /* 0x2 */ u8 time0Min;
    /* 0x3 */ u8 time1Hr;
    /* 0x4 */ u8 time1Min;
    /* 0x5 */ u8 result;
} ScheduleCmdReturnTime; // size = 0x6

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 timeHr;
    /* 0x2 */ u8 timeMin;
    /* 0x3 */ s8 offset;
} ScheduleCmdCheckBeforeTimeS; // size = 0x4

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 timeHr;
    /* 0x2 */ u8 timeMin;
    /* 0x3 */ u8 offsetH;
    /* 0x4 */ u8 offsetL;
} ScheduleCmdCheckBeforeTimeL; // size = 0x5

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ s8 offset;
} ScheduleCmdBranchS; // size = 0x2

typedef struct {
    /* 0x0 */ ScheduleCmdBase base;
    /* 0x1 */ u8 offsetH;
    /* 0x2 */ u8 offsetL;
} ScheduleCmdBranchL; // size = 0x3

#define SCHEDULE_PACK_S16(val) \
    ((val) >> 8) & 0xFF, (val) & 0xFF

#define SCHEDULE_CMD_CHECK_FLAG_S(flag, offset) \
    SCHEDULE_CMD_ID_CHECK_FLAG_S, SCHEDULE_PACK_S16(flag), (offset)

#define SCHEDULE_CMD_CHECK_FLAG_L(flag, offset) \
    SCHEDULE_CMD_ID_CHECK_FLAG_L, SCHEDULE_PACK_S16(flag), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_CHECK_TIME_RANGE_S(startHr, startMin, endHr, endMin, offset) \
    SCHEDULE_CMD_ID_CHECK_TIME_RANGE_S, (startHr), (startMin), (endHr), (endMin), (offset)

#define SCHEDULE_CMD_CHECK_TIME_RANGE_L(startHr, startMin, endHr, endMin, offset) \
    SCHEDULE_CMD_ID_CHECK_TIME_RANGE_L, (startHr), (startMin), (endHr), (endMin), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_RET_VAL_L(result) \
    SCHEDULE_CMD_ID_RET_VAL_L, SCHEDULE_PACK_S16(result)

#define SCHEDULE_CMD_RET_NONE() \
    SCHEDULE_CMD_ID_RET_NONE

#define SCHEDULE_CMD_RET_EMPTY() \
    SCHEDULE_CMD_ID_RET_EMPTY,

#define SCHEDULE_CMD_NOP(unk0, unk1, unk2) \
    SCHEDULE_CMD_ID_NOP, (unk0), (unk1), (unk2)

#define SCHEDULE_CMD_CHECK_MISC_S(which, offset) \
    SCHEDULE_CMD_ID_CHECK_MISC_S, (which), (offset)

#define SCHEDULE_CMD_RET_VAL_S(result) \
    SCHEDULE_CMD_ID_RET_VAL_S, (result)

#define SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(scene, offset) \
    SCHEDULE_CMD_ID_CHECK_NOT_IN_SCENE_S, SCHEDULE_PACK_S16(scene), (offset)

#define SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(scene, offset) \
    SCHEDULE_CMD_ID_CHECK_NOT_IN_SCENE_L, SCHEDULE_PACK_S16(scene), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(day, offset) \
    SCHEDULE_CMD_ID_CHECK_NOT_IN_DAY_S, SCHEDULE_PACK_S16(day), (offset)

#define SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(day, offset) \
    SCHEDULE_CMD_ID_CHECK_NOT_IN_DAY_L, SCHEDULE_PACK_S16(day), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_RET_TIME(time0Hr, time0Min, time1Hr, time1Min, result) \
    SCHEDULE_CMD_ID_RET_TIME, (time0Hr), (time0Min), (time1Hr), (time1Min), (result)

#define SCHEDULE_CMD_CHECK_BEFORE_TIME_S(timeHr, timeMin, offset) \
    SCHEDULE_CMD_ID_CHECK_BEFORE_TIME_S, (timeHr), (timeMin), (offset)

#define SCHEDULE_CMD_CHECK_BEFORE_TIME_L(timeHr, timeMin, offset) \
    SCHEDULE_CMD_ID_CHECK_BEFORE_TIME_L, (timeHr), (timeMin), SCHEDULE_PACK_S16(offset)

#define SCHEDULE_CMD_BRANCH_S(offset) \
    SCHEDULE_CMD_ID_BRANCH_S, (offset)

#define SCHEDULE_CMD_BRANCH_L(offset) \
    SCHEDULE_CMD_ID_BRANCH_L, SCHEDULE_PACK_S16(offset)

#endif
