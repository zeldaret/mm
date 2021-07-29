#ifndef Z_EN_GE2_H
#define Z_EN_GE2_H

#include "global.h"

struct EnGe2;

typedef void (*EnGe2ActionFunc)(struct EnGe2* this, GlobalContext* globalCtx);

typedef struct EnGe2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C4];
    /* 0x0308 */ EnGe2ActionFunc actionFunc;
} EnGe2; // size = 0x30C

extern const ActorInit En_Ge2_InitVars;

#endif // Z_EN_GE2_H
