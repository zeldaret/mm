#ifndef Z_DM_GM_H
#define Z_DM_GM_H

#include "global.h"

struct DmGm;

typedef void (*DmGmActionFunc)(struct DmGm* this, GlobalContext* globalCtx);

typedef struct DmGm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ DmGmActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x14C];
} DmGm; // size = 0x2D8

extern const ActorInit Dm_Gm_InitVars;

#endif // Z_DM_GM_H
