#ifndef Z_EN_WF_H
#define Z_EN_WF_H

#include "global.h"
#include "objects/object_wf/object_wf.h"

struct EnWf;

typedef void (*EnWfActionFunc)(struct EnWf*, PlayState*);

#define ENWF_GET_80(thisx) ((thisx)->params & 0x80)

typedef struct EnWf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[WOLFOS_NORMAL_LIMB_MAX];
    /* 0x20C */ Vec3s morphTable[WOLFOS_NORMAL_LIMB_MAX];
    /* 0x290 */ EnWfActionFunc actionFunc;
    /* 0x294 */ u8 eyeIndex;
    /* 0x295 */ u8 unk_295;
    /* 0x296 */ u8 drawDmgEffType;
    /* 0x298 */ s16 unk_298;
    /* 0x29A */ s16 unk_29A;
    /* 0x29C */ s16 unk_29C;
    /* 0x29E */ s16 unk_29E;
    /* 0x2A0 */ s16 unk_2A0;
    /* 0x2A2 */ u16 unk_2A2;
    /* 0x2A4 */ f32 unk_2A4;
    /* 0x2A8 */ f32 unk_2A8;
    /* 0x2AC */ f32 drawDmgEffAlpha;
    /* 0x2B0 */ f32 drawDmgEffScale;
    /* 0x2B4 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x2B8 */ Vec3f limbPos[10];
    /* 0x330 */ ColliderJntSph collider1;
    /* 0x350 */ ColliderJntSphElement collider1Elements[4];
    /* 0x450 */ ColliderCylinder collider2;
    /* 0x49C */ ColliderCylinder collider3;
} EnWf; // size = 0x4E8

extern const ActorInit En_Wf_InitVars;

#endif // Z_EN_WF_H
