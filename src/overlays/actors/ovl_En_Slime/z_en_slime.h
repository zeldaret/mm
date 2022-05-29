#ifndef Z_EN_SLIME_H
#define Z_EN_SLIME_H

#include "global.h"

struct EnSlime;

typedef void (*EnSlimeActionFunc)(struct EnSlime*, GlobalContext*);

typedef struct EnSlime {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnSlimeActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0xC0];
} EnSlime; // size = 0x208

extern const ActorInit En_Slime_InitVars;

#endif // Z_EN_SLIME_H
