#ifndef Z_EN_M_THUNDER_H
#define Z_EN_M_THUNDER_H

#include "global.h"

struct EnMThunder;

typedef void (*EnMThunderActionFunc)(struct EnMThunder* this, GlobalContext* globalCtx);

typedef struct EnMThunder {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x74];
    /* 0x01B8 */ EnMThunderActionFunc actionFunc;
    /* 0x01BC */ char unk_1BC[0x8];
} EnMThunder; // size = 0x1C4

extern const ActorInit En_M_Thunder_InitVars;

#endif // Z_EN_M_THUNDER_H
