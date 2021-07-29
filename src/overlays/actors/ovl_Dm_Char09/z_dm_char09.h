#ifndef Z_DM_CHAR09_H
#define Z_DM_CHAR09_H

#include "global.h"

struct DmChar09;

typedef void (*DmChar09ActionFunc)(struct DmChar09* this, GlobalContext* globalCtx);

typedef struct DmChar09 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xBC];
    /* 0x0200 */ DmChar09ActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0x2C];
} DmChar09; // size = 0x230

extern const ActorInit Dm_Char09_InitVars;

#endif // Z_DM_CHAR09_H
