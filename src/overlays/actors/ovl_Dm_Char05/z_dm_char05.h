#ifndef Z_DM_CHAR05_H
#define Z_DM_CHAR05_H

#include "global.h"

struct DmChar05;

typedef void (*DmChar05ActionFunc)(struct DmChar05* this, GlobalContext* globalCtx);

typedef struct DmChar05 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ DmChar05ActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x2C];
} DmChar05; // size = 0x1B8

extern const ActorInit Dm_Char05_InitVars;

#endif // Z_DM_CHAR05_H
