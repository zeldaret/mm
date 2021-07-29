#ifndef Z_EN_FU_H
#define Z_EN_FU_H

#include "global.h"

struct EnFu;

typedef void (*EnFuActionFunc)(struct EnFu* this, GlobalContext* globalCtx);

typedef struct EnFu {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnFuActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x37C];
} EnFu; // size = 0x554

extern const ActorInit En_Fu_InitVars;

#endif // Z_EN_FU_H
