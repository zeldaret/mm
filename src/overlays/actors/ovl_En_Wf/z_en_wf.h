#ifndef Z_EN_WF_H
#define Z_EN_WF_H

#include "global.h"

struct EnWf;

typedef void (*EnWfActionFunc)(struct EnWf*, GlobalContext*);

#define ENWF_GET_80(thisx) ((thisx)->params & 0x80)

typedef struct EnWf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[22];
    /* 0x020C */ Vec3s morphTable[22];
    /* 0x0290 */ EnWfActionFunc actionFunc;
    /* 0x0294 */ u8 unk_294;
    /* 0x0295 */ u8 unk_295;
    /* 0x0296 */ u8 drawDmgEffType;
    /* 0x0298 */ s16 unk_298;
    /* 0x029A */ s16 unk_29A;
    /* 0x029C */ s16 unk_29C;
    /* 0x029E */ s16 unk_29E;
    /* 0x02A0 */ s16 unk_2A0;
    /* 0x02A2 */ u16 unk_2A2;
    /* 0x02A4 */ f32 unk_2A4;
    /* 0x02A8 */ f32 unk_2A8;
    /* 0x02AC */ f32 drawDmgEffAlpha;
    /* 0x02B0 */ f32 drawDmgEffScale;
    /* 0x02B4 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x02B8 */ Vec3f limbPos[10];
    /* 0x0330 */ ColliderJntSph collider1;
    /* 0x0350 */ ColliderJntSphElement collider1Elements[4];
    /* 0x0450 */ ColliderCylinder collider2;
    /* 0x049C */ ColliderCylinder collider3;
} EnWf; // size = 0x4E8

extern const ActorInit En_Wf_InitVars;

#endif // Z_EN_WF_H
