#ifndef Z_DM_ZL_H
#define Z_DM_ZL_H

#include "global.h"

struct DmZl;

typedef void (*DmZlActionFunc)(struct DmZl* this, GlobalContext* globalCtx);

typedef struct DmZl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x11C];
    /* 0x0260 */ DmZlActionFunc actionFunc;
    /* 0x0264 */ char unk_264[0x70];
} DmZl; // size = 0x2D4

extern const ActorInit Dm_Zl_InitVars;

#endif // Z_DM_ZL_H
