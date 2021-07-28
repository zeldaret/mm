#ifndef Z_EN_BABA_H
#define Z_EN_BABA_H

#include "global.h"

struct EnBaba;

typedef struct EnBaba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2FC];
} EnBaba; // size = 0x440

extern const ActorInit En_Baba_InitVars;

#endif // Z_EN_BABA_H
