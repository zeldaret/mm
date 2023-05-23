#ifndef Z_EN_SNOWWD_H
#define Z_EN_SNOWWD_H

#include "global.h"

struct EnSnowwd;

typedef void (*EnSnowwdActionFunc)(struct EnSnowwd*, PlayState*);

typedef struct EnSnowwd {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
    /* 0x194 */ EnSnowwdActionFunc actionFunc;
} EnSnowwd; // size = 0x198

#endif // Z_EN_SNOWWD_H
