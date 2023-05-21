#ifndef Z_EN_KITAN_H
#define Z_EN_KITAN_H

#include "global.h"
#include "objects/object_kitan/object_kitan.h"

struct EnKitan;

typedef void (*EnKitanActionFunc)(struct EnKitan*, PlayState*);

typedef struct EnKitan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_KITAN_LIMB_MAX];
    /* 0x206 */ Vec3s morphTable[OBJECT_KITAN_LIMB_MAX];
    /* 0x284 */ ColliderCylinder collider;
    /* 0x2D0 */ s32 textBitSet;
    /* 0x2D4 */ char unk2D4[2];
    /* 0x2D6 */ s16 timer;
    /* 0x2D8 */ EnKitanActionFunc actionFunc;
} EnKitan; // size = 0x2DC

#endif // Z_EN_KITAN_H
