#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"
#include "objects/object_mu/object_mu.h"

struct EnTg;

typedef void (*EnTgActionFunc)(struct EnTg*, PlayState*);

typedef struct EnTgHeartInfo {
    /* 0x00 */ u8 isFirstHeartSpawned; // Whether or not the first heart in the animation is spawned
    /* 0x01 */ u8 firstHeartTimer;     // Set to 16 and counts down while isFirstHeartSpawned
    /* 0x02 */ char unk2[0x2];
    /* 0x04 */ f32 scale; // Set to 0.01f and used in Matrix_Scale
    /* 0x08 */ char unk8[0xC];
    /* 0x14 */ Vec3f firstHeartPos;   // Position of the first heart
    /* 0x20 */ Vec3f unusedZeroVec20; // Set to zeroVec, never read
    /* 0x2C */ Vec3f velocity;        // Set to {0, 1.5, 0}, updates the firstHeartPos y height every frame
    /* 0x38 */ s16 angle;             // Only updated if isFirstHeartSpawned
} EnTgHeartInfo;                      // size = 0x40

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
    /* 0x02F0 */ EnTgHeartInfo enTgHeartInfo[10];
    /* 0x0520 */ char unk330[0x28];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
