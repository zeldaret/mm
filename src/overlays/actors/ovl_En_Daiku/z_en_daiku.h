#ifndef Z_EN_DAIKU_H
#define Z_EN_DAIKU_H

#include "global.h"

struct EnDaiku;

typedef void (*EnDaikuActionFunc)(struct EnDaiku* this, GlobalContext* globalCtx);

typedef struct EnDaiku {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x110];
    /* 0x0254 */ EnDaikuActionFunc actionFunc;
    /* 0x0258 */ char unk_258[0x90];
} EnDaiku; // size = 0x2E8

extern const ActorInit En_Daiku_InitVars;

#endif // Z_EN_DAIKU_H
