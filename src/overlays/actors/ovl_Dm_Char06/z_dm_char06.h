#ifndef Z_DM_CHAR06_H
#define Z_DM_CHAR06_H

#include "global.h"

struct DmChar06;

typedef void (*DmChar06ActionFunc)(struct DmChar06* this, GlobalContext* globalCtx);

typedef struct DmChar06 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x14C];
    /* 0x0290 */ DmChar06ActionFunc actionFunc;
    /* 0x0294 */ char unk_294[0x10];
} DmChar06; // size = 0x2A4

extern const ActorInit Dm_Char06_InitVars;

#endif // Z_DM_CHAR06_H
