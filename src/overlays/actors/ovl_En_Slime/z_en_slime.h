#ifndef Z_EN_SLIME_H
#define Z_EN_SLIME_H

#include "global.h"

struct EnSlime;

typedef void (*EnSlimeActionFunc)(struct EnSlime*, PlayState*);

typedef struct EnSlime {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnSlimeActionFunc actionFunc;
    /* 0x148 */ char unk_148[0xC0];
} EnSlime; // size = 0x208

extern const ActorInit En_Slime_InitVars;

#endif // Z_EN_SLIME_H
