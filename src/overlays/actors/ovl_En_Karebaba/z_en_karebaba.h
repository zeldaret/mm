#ifndef Z_EN_KAREBABA_H
#define Z_EN_KAREBABA_H

#include "global.h"

struct EnKarebaba;

typedef void (*EnKarebabaActionFunc)(struct EnKarebaba*, PlayState*);

enum {
    /* 0 */ ENKAREBABA_0,
    /* 1 */ ENKAREBABA_1,
    /* 2 */ ENKAREBABA_2,
};

typedef struct EnKarebaba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnKarebabaActionFunc actionFunc;
    /* 0x18C */ Vec3s jointTable[8];
    /* 0x1BC */ Vec3s morphTable[8];
    /* 0x1EC */ u8 drawDmgEffType;
    /* 0x1EE */ s16 unk_1EE;
    /* 0x1F0 */ f32 drawDmgEffAlpha;
    /* 0x1F4 */ f32 drawDmgEffScale;
    /* 0x1F8 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x1FC */ Vec3f limbPos[4];
    /* 0x22C */ CollisionPoly* unk_22C;
    /* 0x230 */ ColliderCylinder collider1;
    /* 0x27C */ ColliderCylinder collider2;
} EnKarebaba; // size = 0x2C8

extern const ActorInit En_Karebaba_InitVars;

#endif // Z_EN_KAREBABA_H
