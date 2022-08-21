#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"
#include "objects/object_mu/object_mu.h"

struct EnTg;

typedef void (*EnTgActionFunc)(struct EnTg*, PlayState*);

typedef struct EnTgHeartEffect {
    /* 0x00 */ u8 isEnabled;
    /* 0x01 */ u8 timer;
    /* 0x02 */ char unk2[0x2];
    /* 0x04 */ f32 scale;
    /* 0x08 */ char unk8[0xC];
    /* 0x14 */ Vec3f pos;
    /* 0x20 */ Vec3f unusedZeroVec20;
    /* 0x2C */ Vec3f velocity;
    /* 0x38 */ s16 angle;
} EnTgHeartEffect; // size = 0x40

typedef struct EnTg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTgActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ char unk1D8[0x18];
    /* 0x01F0 */ Vec3s jointTable[HONEY_AND_DARLING_LIMB_MAX];
    /* 0x026E */ Vec3s morphTable[HONEY_AND_DARLING_LIMB_MAX];
    /* 0x02EC */ s16 spawnHeartTimer; // Countdown timer for a new heart spawning above the actor
    /* 0x02EE */ char unk2EE[0x2];
    /* 0x02F0 */ EnTgHeartEffect enTgHeartEffect[10];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
