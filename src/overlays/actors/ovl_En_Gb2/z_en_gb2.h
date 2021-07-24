#ifndef Z_EN_GB2_H
#define Z_EN_GB2_H

#include "global.h"

struct EnGb2;

typedef struct EnGb2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x150];
} EnGb2; // size = 0x294

extern const ActorInit En_Gb2_InitVars;

#endif // Z_EN_GB2_H
