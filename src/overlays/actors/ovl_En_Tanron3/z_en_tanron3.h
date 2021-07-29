#ifndef Z_EN_TANRON3_H
#define Z_EN_TANRON3_H

#include "global.h"

struct EnTanron3;

typedef void (*EnTanron3ActionFunc)(struct EnTanron3* this, GlobalContext* globalCtx);

typedef struct EnTanron3 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1B4];
    /* 0x02F8 */ EnTanron3ActionFunc actionFunc;
} EnTanron3; // size = 0x2FC

extern const ActorInit En_Tanron3_InitVars;

#endif // Z_EN_TANRON3_H
