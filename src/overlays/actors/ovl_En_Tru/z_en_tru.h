#ifndef Z_EN_TRU_H
#define Z_EN_TRU_H

#include "global.h"

struct EnTru;

typedef struct EnTru {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7F0];
} EnTru; // size = 0x934

extern const ActorInit En_Tru_InitVars;

#endif // Z_EN_TRU_H
