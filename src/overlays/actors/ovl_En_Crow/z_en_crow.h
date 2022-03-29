#ifndef Z_EN_CROW_H
#define Z_EN_CROW_H

#include "global.h"
#include "objects/object_crow/object_crow.h"

struct EnCrow;

typedef void (*EnCrowActionFunc)(struct EnCrow*, GlobalContext*);

typedef struct EnCrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnCrowActionFunc actionFunc;
    /* 0x18C */ u8 deathMode;
    /* 0x18E */ s16 timer;
    /* 0x190 */ s16 aimRotX;
    /* 0x192 */ s16 aimRotY;
    /* 0x194 */ Vec3s jointTable[OBJECT_CROW_LIMB_MAX];
    /* 0x1CA */ Vec3s morphTable[OBJECT_CROW_LIMB_MAX];
    /* 0x200 */ ColliderJntSph collider;
    /* 0x220 */ ColliderJntSphElement colliderItems[1];
    /* 0x260 */ Vec3f bodyPartsPos[4];
    /* 0x290 */ f32 effectAlpha;
    /* 0x294 */ f32 steamScale;
    /* 0x298 */ f32 effectScale;
} EnCrow; // size = 0x29C

extern const ActorInit En_Crow_InitVars;

#endif // Z_EN_CROW_H
