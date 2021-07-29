#ifndef Z_ARROW_ICE_H
#define Z_ARROW_ICE_H

#include "global.h"

struct ArrowIce;

typedef void (*ArrowIceActionFunc)(struct ArrowIce* this, GlobalContext* globalCtx);

typedef struct ArrowIce {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ ArrowIceActionFunc actionFunc;
} ArrowIce; // size = 0x164

extern const ActorInit Arrow_Ice_InitVars;

#endif // Z_ARROW_ICE_H
