#ifndef Z_EN_BH_H
#define Z_EN_BH_H

#include "global.h"

struct EnBh;

typedef void (*EnBhActionFunc)(struct EnBh* this, GlobalContext* globalCtx);

typedef struct EnBh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xA4];
    /* 0x01E8 */ EnBhActionFunc actionFunc;
} EnBh; // size = 0x1EC

extern const ActorInit En_Bh_InitVars;

#endif // Z_EN_BH_H
