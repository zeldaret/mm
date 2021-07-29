#ifndef Z_DM_CHAR02_H
#define Z_DM_CHAR02_H

#include "global.h"

struct DmChar02;

typedef void (*DmChar02ActionFunc)(struct DmChar02* this, GlobalContext* globalCtx);

typedef struct DmChar02 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x14C];
    /* 0x0290 */ DmChar02ActionFunc actionFunc;
    /* 0x0294 */ char unk_294[0x60];
} DmChar02; // size = 0x2F4

extern const ActorInit Dm_Char02_InitVars;

#endif // Z_DM_CHAR02_H
