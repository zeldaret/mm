#ifndef Z_EN_PEEHAT_H
#define Z_EN_PEEHAT_H

#include "global.h"

struct EnPeehat;

typedef void (*EnPeehatActionFunc)(struct EnPeehat*, GlobalContext*);

typedef struct EnPeehat {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[24];
    /* 0x188 */ Vec3s morphTable[24];
    /* 0x2A8 */ EnPeehatActionFunc actionFunc;
    /* 0x2AC */ u8 unk_2AC;
    /* 0x2AD */ s8 unk_2AD;
    /* 0x2AE */ u8 drawDmgEffType;
    /* 0x2B0 */ s16 unk_2B0;
    /* 0x2B2 */ s16 unk_2B2;
    /* 0x2B4 */ s16 unk_2B4;
    /* 0x2B6 */ s16 unk_2B6;
    /* 0x2B8 */ f32 unk_2B8;
    /* 0x2BC */ f32 unk_2BC;
    /* 0x2C0 */ f32 unk_2C0;
    /* 0x2C4 */ f32 unk_2C4;
    /* 0x2C8 */ f32 drawDmgEffAlpha;
    /* 0x2CC */ f32 drawDmgEffScale;
    /* 0x2D0 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x2D4 */ Vec3f unk_2D4[2];
    /* 0x2EC */ Vec3f limbPos[18];
    /* 0x3C4 */ ColliderCylinder colliderCylinder;
    /* 0x410 */ ColliderSphere colliderSphere;
    /* 0x468 */ ColliderTris colliderTris;
    /* 0x488 */ ColliderTrisElement colliderTriElements[2];
} EnPeehat; // size = 0x540

extern const ActorInit En_Peehat_InitVars;

#endif // Z_EN_PEEHAT_H
