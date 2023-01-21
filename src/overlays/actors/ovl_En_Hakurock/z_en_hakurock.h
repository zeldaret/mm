#ifndef Z_EN_HAKUROCK_H
#define Z_EN_HAKUROCK_H

#include "global.h"

struct EnHakurock;

typedef void (*EnHakurockActionFunc)(struct EnHakurock*, PlayState*);

typedef enum {
    /* 0x0 */ EN_HAKUROCK_TYPE_UNK_0,
    /* 0x1 */ EN_HAKUROCK_TYPE_BOULDER,
    /* 0x2 */ EN_HAKUROCK_TYPE_UNK_2,
    /* 0x3 */ EN_HAKUROCK_TYPE_STALACTITE,
    /* 0x4 */ EN_HAKUROCK_TYPE_FENCE_PILLAR
} EnHakurockType;

typedef struct EnHakurock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnHakurockActionFunc actionFunc;
    /* 0x148 */ s32 counter;
    /* 0x14C */ ColliderCylinder collider;
} EnHakurock; // size = 0x198

#endif // Z_EN_HAKUROCK_H
