#ifndef Z_EN_KAREBABA_H
#define Z_EN_KAREBABA_H

#include "global.h"

struct EnKarebaba;

typedef void (*EnKarebabaActionFunc)(struct EnKarebaba*, GlobalContext*);

enum {
    /* 0 */ ENKAREBABA_0,
    /* 1 */ ENKAREBABA_1,
    /* 2 */ ENKAREBABA_2,
};

typedef struct EnKarebaba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnKarebabaActionFunc actionFunc;
    /* 0x018C */ Vec3s jointTable[8];
    /* 0x01BC */ Vec3s morphTable[8];
    /* 0x01EC */ u8 drawDmgEffType;
    /* 0x01EE */ s16 unk_1EE;
    /* 0x01F0 */ f32 drawDmgEffAlpha;
    /* 0x01F4 */ f32 drawDmgEffScale;
    /* 0x01F8 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x01FC */ Vec3f limbPos[4];
    /* 0x022C */ CollisionPoly* unk_22C;
    /* 0x0230 */ ColliderCylinder collider1;
    /* 0x027C */ ColliderCylinder collider2;
} EnKarebaba; // size = 0x2C8

extern const ActorInit En_Karebaba_InitVars;

#endif // Z_EN_KAREBABA_H
