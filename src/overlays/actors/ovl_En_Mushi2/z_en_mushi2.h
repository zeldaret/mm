#ifndef Z_EN_MUSHI2_H
#define Z_EN_MUSHI2_H

#include "global.h"

struct EnMushi2;

typedef struct EnMushi2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x230];
} EnMushi2; // size = 0x374

extern const ActorInit En_Mushi2_InitVars;

#endif // Z_EN_MUSHI2_H
