#ifndef Z_EN_ENCOUNT1_H
#define Z_EN_ENCOUNT1_H

#include "global.h"

struct EnEncount1;

typedef struct EnEncount1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} EnEncount1; // size = 0x164

extern const ActorInit En_Encount1_InitVars;

#endif // Z_EN_ENCOUNT1_H
