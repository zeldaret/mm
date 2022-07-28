#ifndef Z_EN_SYATEKI_WF_H
#define Z_EN_SYATEKI_WF_H

#include "global.h"
#include "objects/object_wf/object_wf.h"

#define EN_SYATEKI_WF_GET_PARAM_F0(thisx) (((thisx)->params & 0xF0) >> 4)
#define EN_SYATEKI_WF_GET_NUMBER(thisx) (((thisx)->params & 0xFF00) >> 8)
#define EN_SYATEKI_WF_PARAMS(number, unkF0, unused) (((number << 8) & 0xFF00) | ((unkF0 << 4) & 0xF0) | (unused & 0xF))

struct EnSyatekiWf;

typedef void (*EnSyatekiWfActionFunc)(struct EnSyatekiWf*, PlayState*);

typedef struct EnSyatekiWf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[WOLFOS_NORMAL_LIMB_MAX];
    /* 0x20C */ Vec3s morphTable[WOLFOS_NORMAL_LIMB_MAX];
    /* 0x290 */ UNK_TYPE1 unk_290[0x4];
    /* 0x294 */ EnSyatekiWfActionFunc actionFunc;
    /* 0x298 */ s16 unk_298;
    /* 0x29A */ s16 unk_29A;
    /* 0x29C */ s16 unk_29C;
    /* 0x2A0 */ Vec3s* unk_2A0;
    /* 0x2A4 */ s16 unk_2A4;
    /* 0x2A6 */ s16 unk_2A6;
    /* 0x2A8 */ s16 unk_2A8;
    /* 0x2AC */ f32 unk_2AC;
    /* 0x2B0 */ u8 eyeIndex;
    /* 0x2B4 */ ColliderCylinder unk_2B4;
    /* 0x300 */ ColliderCylinder unk_300;
    /* 0x34C */ ColliderJntSph unk_34C;
    /* 0x36C */ ColliderJntSphElement unk_36C[1];
    /* 0x3AC */ UNK_TYPE1 unk_3AC[0x20];
} EnSyatekiWf; // size = 0x3CC

extern const ActorInit En_Syateki_Wf_InitVars;

#endif // Z_EN_SYATEKI_WF_H
