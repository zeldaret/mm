#ifndef Z_EN_SNOWWD_H
#define Z_EN_SNOWWD_H

#include "global.h"

struct EnSnowwd;

typedef void (*EnSnowwdActionFunc)(struct EnSnowwd*, PlayState*);

typedef struct EnSnowwd {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ s16 unk190;
    /* 0x194 */ EnSnowwdActionFunc actionFunc;
} EnSnowwd; // size = 0x198

#endif // Z_EN_SNOWWD_H
