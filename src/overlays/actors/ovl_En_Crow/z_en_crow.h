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
    /* 0x18C */ u8 unk18C;
    /* 0x18D */ char pad18D[1];
    /* 0x18E */ s16 timer;
    /* 0x190 */ s16 unk190;
    /* 0x192 */ s16 unk192;
    /* 0x194 */ Vec3s jointTable[9];
    /* 0x1CA */ Vec3s morphTable[9];
    /* 0x200 */ ColliderJntSph collider;
    /* 0x220 */ ColliderJntSphElement unk220;
    /* 0x260 */ Vec3f unk260[4];
    /* 0x290 */ f32 unk290;
    /* 0x294 */ f32 unk294;
    /* 0x298 */ f32 unk298;
} EnCrow; // size = 0x29C

extern const ActorInit En_Crow_InitVars;

#endif // Z_EN_CROW_H
