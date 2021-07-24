#ifndef Z_EN_ENCOUNT3_H
#define Z_EN_ENCOUNT3_H

#include "global.h"

struct EnEncount3;

typedef struct EnEncount3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} EnEncount3; // size = 0x1CC

extern const ActorInit En_Encount3_InitVars;

#endif // Z_EN_ENCOUNT3_H
