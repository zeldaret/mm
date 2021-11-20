#ifndef Z_EN_FALL_H
#define Z_EN_FALL_H

#include "global.h"

#define EN_FALL_SCALE(thisx) ((thisx)->params & 0x7F)
#define EN_FALL_TYPE(thisx) (((thisx)->params & 0xF80) >> 7)

typedef enum {
    EN_FALL_TYPE_TERMINA_FIELD_MOON,
    EN_FALL_TYPE_TITLE_SCREEN_MOON,
    EN_FALL_TYPE_CRASHING_MOON,
    EN_FALL_TYPE_CRASH_FIRE_BALL,
    EN_FALL_TYPE_CRASH_RISING_DEBRIS,
    EN_FALL_TYPE_UNK_5, // ignores LOD?
    EN_FALL_TYPE_REGULAR_GAMEPLAY_MOON,
    EN_FALL_TYPE_STOPPED_MOON_CLOSED_MOUTH,
    EN_FALL_TYPE_MOONS_TEAR,
    EN_FALL_TYPE_CLOCK_TOWER_MOON,
    EN_FALL_TYPE_STOPPED_MOON_OPEN_MOUTH,
    EN_FALL_TYPE_CRASH_FIRE_RING,
    EN_FALL_TYPE_INVERTED_STONE_TOWER_GAMEPLAY_MOON,
} EnFallType;

struct EnFall;

typedef void (*EnFallActionFunc)(struct EnFall*, GlobalContext*);

typedef struct EnFall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s16 dayStartTime;
    /* 0x146 */ s16 currentDay;
    /* 0x148 */ u8 objIndex;
    /* 0x14C */ f32 scale;
    /* 0x150 */ f32 unk_150;
    /* 0x154 */ u16 unk_154;
    /* 0x158 */ s32 unk_158;
    /* 0x15C */ s16 unk_15C;
    /* 0x15E */ s16 unk_15E;
    /* 0x160 */ EnFallActionFunc actionFunc;
} EnFall; // size = 0x164

extern const ActorInit En_Fall_InitVars;

#endif // Z_EN_FALL_H
