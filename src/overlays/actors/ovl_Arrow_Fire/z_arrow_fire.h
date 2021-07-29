#ifndef Z_ARROW_FIRE_H
#define Z_ARROW_FIRE_H

#include "global.h"

struct ArrowFire;

typedef void (*ArrowFireActionFunc)(struct ArrowFire* this, GlobalContext* globalCtx);

typedef struct ArrowFire {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x114];
    /* 0x0258 */ ArrowFireActionFunc actionFunc;
    /* 0x025C */ char unk_25C[0x8];
} ArrowFire; // size = 0x264

extern const ActorInit Arrow_Fire_InitVars;

#endif // Z_ARROW_FIRE_H
