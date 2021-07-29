#ifndef Z_EN_SELLNUTS_H
#define Z_EN_SELLNUTS_H

#include "global.h"

struct EnSellnuts;

typedef void (*EnSellnutsActionFunc)(struct EnSellnuts* this, GlobalContext* globalCtx);

typedef struct EnSellnuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x194];
    /* 0x02D8 */ EnSellnutsActionFunc actionFunc;
    /* 0x02DC */ char unk_2DC[0x9C];
} EnSellnuts; // size = 0x378

extern const ActorInit En_Sellnuts_InitVars;

#endif // Z_EN_SELLNUTS_H
