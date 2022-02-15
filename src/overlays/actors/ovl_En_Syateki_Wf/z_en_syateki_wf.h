#ifndef Z_EN_SYATEKI_WF_H
#define Z_EN_SYATEKI_WF_H

#include "global.h"

#define EN_SYATEKI_WF_GET_PARAM_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

struct EnSyatekiWf;

typedef void (*EnSyatekiWfActionFunc)(struct EnSyatekiWf*, GlobalContext*);

typedef struct EnSyatekiWf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[22];
    /* 0x20C */ Vec3s morphTable[22];
    /* 0x290 */ char unk_290[0x4];
    /* 0x294 */ EnSyatekiWfActionFunc actionFunc;
    /* 0x298 */ s16 unk_298;
    /* 0x29A */ char unk_29A[0x2];
    /* 0x29C */ s16 unk_29C;
    /* 0x29E */ char unk_29E[0x2];
    /* 0x2A0 */ Vec3s* unk_2A0;
    /* 0x2A4 */ s16 unk_2A4;
    /* 0x2A6 */ s16 unk_2A6;
    /* 0x2A8 */ char unk_2A8[0x4];
    /* 0x2AC */ f32 unk_2AC;
    /* 0x2B0 */ s8 unk_2B0;
    /* 0x2B1 */ char unk_2B1[0x3];
    /* 0x2B4 */ ColliderCylinder unk_2B4;
    /* 0x300 */ ColliderCylinder unk_300;
    /* 0x34C */ ColliderJntSph unk_34C;
    /* 0x36C */ ColliderJntSphElement unk_36C;
    /* 0x3AC */ char unk_3AC[0x20];
} EnSyatekiWf; // size = 0x3CC

extern const ActorInit En_Syateki_Wf_InitVars;

#endif // Z_EN_SYATEKI_WF_H
