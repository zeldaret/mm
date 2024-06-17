#ifndef Z_EN_MINIDEATH_H
#define Z_EN_MINIDEATH_H

#include "global.h"

struct EnMinideath;

typedef void (*EnMinideathActionFunc)(struct EnMinideath*, PlayState*);

#define MINIDEATH_NUM_EFFECTS 3

// "animation" length
#define MINIDEATH_ANIM_LENGTH 9

typedef enum {
    MINIDEATH_ACTION_CONTINUE,  // continue with current action until it is changed
    MINIDEATH_ACTION_SCATTER,   // scatter after light arrows?
    MINIDEATH_ACTION_RETURN,   // gomess damaged
    MINIDEATH_ACTION_START_SWARM,
    MINIDEATH_ACTION_SWARM,     // chase player?
    MINIDEATH_ACTION_DEATH_2,   // death cs part 3
    MINIDEATH_ACTION_DEATH_1,   // death cs part 1
    MINIDEATH_ACTION_INTRO_1,   // intro cs part 2
    MINIDEATH_ACTION_INTRO_2,   // intro cs part 5 (1)
    MINIDEATH_ACTION_INTRO_3    // intro cs part 5 (2)
} MinideathAction;

typedef struct {
    /* 0x00 */ u8 animFrame;
    /* 0x01 */ u8 state;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f vel;
    /* 0x1C */ Vec3s angle;
    /* 0x22 */ s16 timer;
} MiniDeathEffect; // size = 0x24

typedef struct EnMinideath {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMinideathActionFunc actionFunc;
    /* 0x0148 */ u8 number;
    /* 0x0149 */ u8 crowdState;
    /* 0x014A */ s16 timer;
    /* 0x014C */ s16 spawnShapeYaw;
    /* 0x014E */ s16 attackTimer;
    /* 0x0150 */ Vec3s moveDirection;
    /* 0x0158 */ f32 initialHeightDiffFromParent;
    /* 0x015C */ Actor* targetActor;
    /* 0x0160 */ MiniDeathEffect effects[MINIDEATH_NUM_EFFECTS];
    /* 0x01CC */ ColliderJntSph collider;
    /* 0x01EC */ ColliderJntSphElement colliderElements[MINIDEATH_NUM_EFFECTS];
} EnMinideath; // size = 0x2AC

#endif // Z_EN_MINIDEATH_H
