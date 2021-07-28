#ifndef Z_EN_DODONGO_H
#define Z_EN_DODONGO_H

#include "global.h"

struct EnDodongo;

typedef struct EnDodongo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6D0];
} EnDodongo; // size = 0x814

extern const ActorInit En_Dodongo_InitVars;

#endif // Z_EN_DODONGO_H
