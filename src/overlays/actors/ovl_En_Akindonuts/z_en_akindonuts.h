#ifndef Z_EN_AKINDONUTS_H
#define Z_EN_AKINDONUTS_H

#include "global.h"

struct EnAkindonuts;

typedef struct EnAkindonuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x228];
} EnAkindonuts; // size = 0x36C

extern const ActorInit En_Akindonuts_InitVars;

#endif // Z_EN_AKINDONUTS_H
