#ifndef Z_EN_SNOWWD_H
#define Z_EN_SNOWWD_H

#include "global.h"

struct EnSnowwd;

typedef struct EnSnowwd {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnSnowwd; // size = 0x198

extern const ActorInit En_Snowwd_InitVars;

#endif // Z_EN_SNOWWD_H
