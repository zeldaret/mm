#ifndef Z_EN_TANRON5_H
#define Z_EN_TANRON5_H

#include "global.h"

struct EnTanron5;

typedef struct EnTanron5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x60];
} EnTanron5; // size = 0x1A4

extern const ActorInit En_Tanron5_InitVars;

#endif // Z_EN_TANRON5_H
