#ifndef Z_EN_TANRON5_H
#define Z_EN_TANRON5_H

#include "global.h"

struct EnTanron5;

#define ENTANRON5_GET(thisx) ((thisx)->params)

#define ENTANRON5_0 0
#define ENTANRON5_100 100
#define ENTANRON5_107 107
#define ENTANRON5_108 108
#define ENTANRON5_110 110

typedef struct EnTanron5 {
    /* 0x000 */ Actor actor;
    /* 0x0144 */ s16 unk_144;
    /* 0x0148 */ Gfx* unk_148;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ s16 unk_198;
    /* 0x019A */ s16 unk_19A;
    /* 0x019C */ f32 unk_19C;
    /* 0x01A0 */ u8 unk_1A0;
    /* 0x01A1 */ u8 unk_1A1;
} EnTanron5; // size = 0x1A4

extern const ActorInit En_Tanron5_InitVars;

#endif // Z_EN_TANRON5_H
