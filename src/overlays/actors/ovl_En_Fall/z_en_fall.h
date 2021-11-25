#ifndef Z_EN_FALL_H
#define Z_EN_FALL_H

#include "global.h"

#define EN_FALL_SCALE(thisx) ((thisx)->params & 0x7F)
#define EN_FALL_TYPE(thisx) (((thisx)->params & 0xF80) >> 7)

#define EN_FALL_FLAG_FIRE_BALL_BRIGHTENS (1 << 0)
#define EN_FALL_FLAG_FIRE_RING_APPEARS (1 << 1)

typedef enum {
    EN_FALL_TYPE_TERMINA_FIELD_MOON,
    EN_FALL_TYPE_TITLE_SCREEN_MOON,
    EN_FALL_TYPE_CRASHING_MOON,
    EN_FALL_TYPE_CRASH_FIRE_BALL,
    EN_FALL_TYPE_CRASH_RISING_DEBRIS,
    EN_FALL_TYPE_LODMOON_NO_LERP, // unused in final game
    EN_FALL_TYPE_LODMOON,
    EN_FALL_TYPE_STOPPED_MOON_CLOSED_MOUTH,
    EN_FALL_TYPE_MOONS_TEAR,
    EN_FALL_TYPE_CLOCK_TOWER_MOON,
    EN_FALL_TYPE_STOPPED_MOON_OPEN_MOUTH,
    EN_FALL_TYPE_CRASH_FIRE_RING,
    EN_FALL_TYPE_LODMOON_INVERTED_STONE_TOWER,
} EnFallType;

struct EnFall;

typedef void (*EnFallActionFunc)(struct EnFall*, GlobalContext*);

typedef struct EnFall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s16 dayStartTime;
    /* 0x146 */ s16 currentDay;
    /* 0x148 */ u8 objIndex;
    /* 0x14C */ f32 scale;
    /* 0x150 */ union {
                    f32 eyeGlowIntensity;
                    f32 fireBallIntensity;
                    f32 fireRingOpacity;
                };
    /* 0x154 */ u16 flags;
    /* 0x158 */ union {
                    s32 fireBallOpacity;
                    s32 activeDebrisParticleCount;
                };
    /* 0x15C */ union {
                    s16 fireBallYTexScroll1;
                    s16 fireWallYScale;
                };
    /* 0x15E */ s16 fireBallYTexScroll2;
    /* 0x160 */ EnFallActionFunc actionFunc;
} EnFall; // size = 0x164

extern const ActorInit En_Fall_InitVars;

#endif // Z_EN_FALL_H
