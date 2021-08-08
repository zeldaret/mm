#ifndef Z_EN_BOMBERS_H
#define Z_EN_BOMBERS_H

#include "global.h"

struct EnBombers;

typedef void (*EnBombersActionFunc)(struct EnBombers* this, GlobalContext* globalCtx);

typedef struct EnBombers {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnBombersActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0x8C];
} EnBombers; // size = 0x314

extern const ActorInit En_Bombers_InitVars;

#endif // Z_EN_BOMBERS_H
