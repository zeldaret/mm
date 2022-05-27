#ifndef Z_EN_BOMBF_H
#define Z_EN_BOMBF_H

#include "global.h"

struct EnBombf;

typedef void (*EnBombfActionFunc)(struct EnBombf*, GlobalContext*);

#define ENBOMBF_GET(thisx) ((thisx)->params)

#define ENBOMBF_0 0
#define ENBOMBF_1 1

typedef struct EnBombf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder colliderCylinder;
    /* 0x0190 */ ColliderJntSph colliderJntSph;
    /* 0x01B0 */ ColliderJntSphElement colliderJntSphElements[1];
    /* 0x01F0 */ s16 timer;
    /* 0x01F4 */ EnBombfActionFunc actionFunc;
    /* 0x01F8 */ s32 unk_1F8;
    /* 0x01FC */ u8 unk_1FC;
    /* 0x01FE */ s16 unk_1FE;
    /* 0x0200 */ f32 unk_200;
    /* 0x0204 */ f32 unk_204;
} EnBombf; // size = 0x208

extern const ActorInit En_Bombf_InitVars;

#endif // Z_EN_BOMBF_H
