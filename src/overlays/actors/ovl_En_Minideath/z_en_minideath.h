#ifndef Z_EN_MINIDEATH_H
#define Z_EN_MINIDEATH_H

#include "global.h"

struct EnMinideath;

typedef void (*EnMinideathActionFunc)(struct EnMinideath*, PlayState*);

// "animation" length
#define MINIDEATH_ANIM_LENGTH 9

typedef enum {
    MINIDEATH_ACTION_CONTINUE,  // continue with current action until it is changed
    MINIDEATH_ACTION_1,         // scatter after light arrows?
    MINIDEATH_ACTION_2,         // gomess damaged
    MINIDEATH_ACTION_3,
    MINIDEATH_ACTION_4,         // chase player?
    MINIDEATH_ACTION_DIE,       // dead?
    MINIDEATH_ACTION_6,
    MINIDEATH_ACTION_7,
    MINIDEATH_ACTION_8,
    MINIDEATH_ACTION_9
} MinideathAction;

typedef struct {
    /* 0x00 */ u8 animFrame;
    /* 0x01 */ u8 unk_1;
    /* 0x04 */ Vec3f unk_4;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[0x2];
    /* 0x22 */ s16 unk_22;
} MiniDeathStruct; // size = 0x24

typedef struct EnMinideath {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMinideathActionFunc actionFunc;
    /* 0x0148 */ u8 number;
    /* 0x0149 */ u8 unk_149;
    /* 0x014A */ s16 timer;
    /* 0x014C */ s16 spawnShapeRot;
    /* 0x014E */ s16 attackTimer;
    /* 0x0150 */ Vec3s unk_150; // move direction?
    /* 0x0158 */ f32 unk_158;
    /* 0x015C */ Actor* unk_15C;
    /* 0x0160 */ MiniDeathStruct unk_160[3];
    /* 0x01CC */ ColliderJntSph collider;
    /* 0x01EC */ ColliderJntSphElement colliderElements[3];
} EnMinideath; // size = 0x2AC

#endif // Z_EN_MINIDEATH_H
