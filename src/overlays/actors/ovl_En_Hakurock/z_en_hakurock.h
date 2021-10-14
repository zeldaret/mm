#ifndef Z_EN_HAKUROCK_H
#define Z_EN_HAKUROCK_H

#include "global.h"

struct EnHakurock;

typedef void (*EnHakurockActionFunc)(struct EnHakurock*, GlobalContext*);

typedef enum {
    /* 0x1 */ OBSTICAL_ROCK,
    /* 0x2 */ OBSTICAL_UNK,
    /* 0x3 */ OBSTICAL_STALAGMITE
} ObsticalType;

typedef struct EnHakurock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnHakurockActionFunc actionFunc;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ ColliderCylinder collider; // size = 0x4C
} EnHakurock; // size = 0x198

extern const ActorInit En_Hakurock_InitVars;

#endif // Z_EN_HAKUROCK_H
