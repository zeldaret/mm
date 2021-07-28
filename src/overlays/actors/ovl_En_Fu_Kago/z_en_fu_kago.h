#ifndef Z_EN_FU_KAGO_H
#define Z_EN_FU_KAGO_H

#include "global.h"

struct EnFuKago;

typedef struct EnFuKago {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1FC];
} EnFuKago; // size = 0x340

extern const ActorInit En_Fu_Kago_InitVars;

#endif // Z_EN_FU_KAGO_H
