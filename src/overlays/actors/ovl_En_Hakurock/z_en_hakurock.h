#ifndef Z_EN_HAKUROCK_H
#define Z_EN_HAKUROCK_H

#include "global.h"

struct EnHakurock;

typedef struct EnHakurock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnHakurock; // size = 0x198

extern const ActorInit En_Hakurock_InitVars;

#endif // Z_EN_HAKUROCK_H
