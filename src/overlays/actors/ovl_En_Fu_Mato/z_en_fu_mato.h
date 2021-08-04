#ifndef Z_EN_FU_MATO_H
#define Z_EN_FU_MATO_H

#include "global.h"

struct EnFuMato;

typedef void (*EnFuMatoActionFunc)(struct EnFuMato* this, GlobalContext* globalCtx);

typedef struct EnFuMato {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ EnFuMatoActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x1AC];
} EnFuMato; // size = 0x30C

extern const ActorInit En_Fu_Mato_InitVars;

#endif // Z_EN_FU_MATO_H
