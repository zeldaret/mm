#ifndef Z_EN_HAKUROCK_H
#define Z_EN_HAKUROCK_H

#include "global.h"

struct EnHakurock;

typedef void (*EnHakurockActionFunc)(struct EnHakurock*, GlobalContext*);

typedef enum {
    /* 0x0 */ UNK_0,
    /* 0x1 */ BOULDER,
    /* 0x2 */ UNK_2,
    /* 0x3 */ STALAGMITE,
    /* 0x4 */ FENCE_PILLAR
} EnHakurockType;

typedef struct EnHakurock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnHakurockActionFunc actionFunc;
    /* 0x148 */ s32 counter;
    /* 0x14C */ ColliderCylinder collider;
} EnHakurock; // size = 0x198

extern const ActorInit En_Hakurock_InitVars;

#endif // Z_EN_HAKUROCK_H
