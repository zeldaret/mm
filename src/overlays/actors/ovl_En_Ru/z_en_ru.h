#ifndef Z_EN_RU_H
#define Z_EN_RU_H

#include "global.h"

struct EnRu;

typedef void (*EnRuActionFunc)(struct EnRu*, PlayState*);

typedef struct EnRu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnRuActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x30C];
} EnRu; // size = 0x454

extern const ActorInit En_Ru_InitVars;

#endif // Z_EN_RU_H
