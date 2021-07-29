#ifndef Z_DM_STK_H
#define Z_DM_STK_H

#include "global.h"

struct DmStk;

typedef void (*DmStkActionFunc)(struct DmStk* this, GlobalContext* globalCtx);

typedef struct DmStk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x14C];
    /* 0x0290 */ DmStkActionFunc actionFunc;
    /* 0x0294 */ char unk_294[0xA8];
} DmStk; // size = 0x33C

extern const ActorInit Dm_Stk_InitVars;

#endif // Z_DM_STK_H
