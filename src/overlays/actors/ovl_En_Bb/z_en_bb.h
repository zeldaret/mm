#ifndef Z_EN_BB_H
#define Z_EN_BB_H

#include "global.h"

#define EN_BB_GET_RIGHT_SHIFT_8_PARAM(thisx) (((thisx)->params >> 8) & 0xFF)

struct EnBb;

typedef void (*EnBbActionFunc)(struct EnBb*, GlobalContext*);

typedef struct EnBb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ EnBbActionFunc actionFunc;
    /* 0x24C */ char unk_24C[0x14];
    /* 0x260 */ f32 unk_260;
    /* 0x264 */ f32 unk_264;
    /* 0x268 */ f32 unk_268;
    /* 0x26C */ char pad_26C[0x88];
    /* 0x2F4 */ ColliderSphere collider;
} EnBb; // size = 0x34C

extern const ActorInit En_Bb_InitVars;

#endif // Z_EN_BB_H
