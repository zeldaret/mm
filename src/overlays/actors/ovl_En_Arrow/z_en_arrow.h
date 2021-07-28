#ifndef Z_EN_ARROW_H
#define Z_EN_ARROW_H

#include "global.h"

struct EnArrow;

typedef struct EnArrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x134];
} EnArrow; // size = 0x278

extern const ActorInit En_Arrow_InitVars;

#endif // Z_EN_ARROW_H
