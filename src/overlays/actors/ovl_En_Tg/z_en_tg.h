#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"

struct EnTg;

typedef void (*EnTgActionFunc)(struct EnTg*, PlayState*);

typedef struct EnTgUnkStruct {
    /* 0x00 */ u8 isSecondHeartSpawned; // whether or not the second heart in the animation is spawned
    /* 0x01 */ u8 secondHeartTimer;     // set to 16 and counts down
    /* 0x02 */ char unk2[0x2];
    /* 0x04 */ f32 scale;
    /* 0x08 */ char unk8[0xC];
    /* 0x14 */ Vec3f secondHeartPos;
    /* 0x20 */ Vec3f unusedZeroVec20; // set to zeroVec, never read
    /* 0x2C */ Vec3f heartVelocity;   // set to {0, 1.5, 0}
    /* 0x38 */ s16 unk38;             // only updated if isSecondHeartSpawned
} EnTgUnkStruct;                      // size = 0x40

typedef struct EnTg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTgActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ char unk1D8[0x18];
    /* 0x01F0 */ Vec3s jointTable[21];
    /* 0x026E */ Vec3s morphTable[21];
    /* 0x02EC */ s16 spawnHeartTimer;
    /* 0x02EE */ char unk2EE[0x2];
    /* 0x02F0 */ EnTgUnkStruct enTgUnkStruct;
    /* 0x0330 */ char unk330[0x21C];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
