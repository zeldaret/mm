#ifndef Z_EN_ST_H
#define Z_EN_ST_H

#include "global.h"

struct EnSt;

typedef struct EnSt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x40C];
} EnSt; // size = 0x550

extern const ActorInit En_St_InitVars;

#endif // Z_EN_ST_H
