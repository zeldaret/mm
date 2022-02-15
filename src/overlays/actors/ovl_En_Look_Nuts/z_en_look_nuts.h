#ifndef Z_EN_LOOK_NUTS_H
#define Z_EN_LOOK_NUTS_H

#include "global.h"
#include "objects/object_dnk/object_dnk.h"

struct EnLookNuts;

typedef void (*EnLookNutsActionFunc)(struct EnLookNuts*, GlobalContext*);

typedef struct EnLookNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[OBJECT_DNK_LIMB_MAX];
    /* 0x01CA */ Vec3s morphTable[OBJECT_DNK_LIMB_MAX];
    /* 0x020C */ EnLookNutsActionFunc actionFunc;
    /* 0x0210 */ Path *path;
    /* 0x0214 */ s16 unk214;
    /* 0x0216 */ s16 eyeState;
    /* 0x0218 */ s16 blinkTimer;
    /* 0x021A */ s16 unk21A;
    /* 0x021C */ s16 unk21C;
    /* 0x021E */ s16 unk21E;
    /* 0x0220 */ s16 unk220;
    /* 0x0222 */ s16 isPlayerDetected;
    /* 0x0224 */ s16 unk224;
    /* 0x0226 */ s16 spawnIndex;
    /* 0x0228 */ s32 unk228;
    /* 0x022C */ Vec3f headRotation;
    /* 0x0238 */ Vec3f unk238;
    /* 0x0244 */ ColliderCylinder collider;
} EnLookNuts; // size = 0x290

extern const ActorInit En_Look_Nuts_InitVars;

#endif // Z_EN_LOOK_NUTS_H
