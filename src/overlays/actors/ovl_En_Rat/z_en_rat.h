#ifndef Z_EN_RAT_H
#define Z_EN_RAT_H

#include "global.h"

#define ENRAT_GET_8000(thisx) ((thisx)->params & 0x8000)
#define ENRAT_GET_FF(thisx) ((thisx)->params & 0xFF)

struct EnRat;

typedef struct EnRat {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ char unk_188[0x8];
    /* 0x190 */ s16 unk_190;
    /* 0x192 */ char unk_192[0x2];
    /* 0x194 */ Vec3s jointTable[10];
    /* 0x1D0 */ Vec3s morphTable[10];
    /* 0x20C */ char unk_20C[0x4C];
    /* 0x258 */ f32 unk_258;
    /* 0x25C */ char unk_25C[0x4];
    /* 0x260 */ s32 unk_260;
    /* 0x264 */ s32 unk_264;
    /* 0x268 */ ColliderSphere collider;
} EnRat; // size = 0x2C0

extern const ActorInit En_Rat_InitVars;

#endif // Z_EN_RAT_H
