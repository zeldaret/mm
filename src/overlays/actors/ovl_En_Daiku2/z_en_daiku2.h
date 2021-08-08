#ifndef Z_EN_DAIKU2_H
#define Z_EN_DAIKU2_H

#include "global.h"

struct EnDaiku2;

typedef void (*EnDaiku2ActionFunc)(struct EnDaiku2* this, GlobalContext* globalCtx);

typedef struct EnDaiku2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x110];
    /* 0x0254 */ EnDaiku2ActionFunc actionFunc;
    /* 0x0258 */ char unk_258[0xB70];
} EnDaiku2; // size = 0xDC8

extern const ActorInit En_Daiku2_InitVars;

#endif // Z_EN_DAIKU2_H
