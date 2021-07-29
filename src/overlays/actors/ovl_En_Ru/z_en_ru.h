#ifndef Z_EN_RU_H
#define Z_EN_RU_H

#include "global.h"

struct EnRu;

typedef void (*EnRuActionFunc)(struct EnRu* this, GlobalContext* globalCtx);

typedef struct EnRu {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnRuActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x30C];
} EnRu; // size = 0x454

extern const ActorInit En_Ru_InitVars;

#endif // Z_EN_RU_H
