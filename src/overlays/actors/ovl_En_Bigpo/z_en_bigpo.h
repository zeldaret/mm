#ifndef Z_EN_BIGPO_H
#define Z_EN_BIGPO_H

#include "global.h"

struct EnBigpo;

typedef struct EnBigpo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x254];
} EnBigpo; // size = 0x398

extern const ActorInit En_Bigpo_InitVars;

#endif // Z_EN_BIGPO_H
