#ifndef Z_EN_STH2_H
#define Z_EN_STH2_H

#include "global.h"

struct EnSth2;

typedef struct EnSth2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10C];
} EnSth2; // size = 0x250

extern const ActorInit En_Sth2_InitVars;

#endif // Z_EN_STH2_H
