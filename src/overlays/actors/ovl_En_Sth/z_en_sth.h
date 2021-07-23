#ifndef Z_EN_STH_H
#define Z_EN_STH_H

#include "global.h"

struct EnSth;

typedef struct EnSth {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x160];
} EnSth; // size = 0x2A4

extern const ActorInit En_Sth_InitVars;

#endif // Z_EN_STH_H
