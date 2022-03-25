#ifndef Z_EN_KAME_H
#define Z_EN_KAME_H

#include "global.h"

struct EnKame;

typedef void (*EnKameActionFunc)(struct EnKame*, GlobalContext*);

typedef struct EnKame {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime1;
    /* 0x0188 */ Vec3s jointTable1[13];
    /* 0x01D6 */ Vec3s morphTable1[13];
    /* 0x0224 */ SkelAnime skelAnime2;
    /* 0x0268 */ Vec3s jointTable2[4];
    /* 0x0280 */ Vec3s morphTable2[4];
    /* 0x0298 */ EnKameActionFunc actionFunc;
    /* 0x029C */ u8 unk_29C;
    /* 0x029D */ u8 drawDmgEffType;
    /* 0x029E */ s16 unk_29E;
    /* 0x02A0 */ s16 unk_2A0;
    /* 0x02A2 */ s16 unk_2A2;
    /* 0x02A4 */ s16 unk_2A4;
    /* 0x02A6 */ s16 unk_2A6;
    /* 0x02A8 */ f32 unk_2A8;
    /* 0x02AC */ f32 unk_2AC;
    /* 0x02B0 */ f32 drawDmgEffAlpha;
    /* 0x02B4 */ f32 drawDmgEffScale;
    /* 0x02B8 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x02BC */ Vec3f unk_2BC;
    /* 0x02C8 */ Vec3f limbPos[10];
    /* 0x0340 */ ColliderCylinder collider;
} EnKame; // size = 0x38C

extern const ActorInit En_Kame_InitVars;

#endif // Z_EN_KAME_H
