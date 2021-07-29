#ifndef Z_EN_AH_H
#define Z_EN_AH_H

#include "global.h"

struct EnAh;

typedef void (*EnAhActionFunc)(struct EnAh* this, GlobalContext* globalCtx);

typedef struct EnAh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnAhActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x178];
} EnAh; // size = 0x304

extern const ActorInit En_Ah_InitVars;

#endif // Z_EN_AH_H
