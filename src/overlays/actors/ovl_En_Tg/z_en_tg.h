#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"

struct EnTg;

typedef struct EnTg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x404];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
