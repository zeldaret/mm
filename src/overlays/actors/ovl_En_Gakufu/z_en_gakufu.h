#ifndef Z_EN_GAKUFU_H
#define Z_EN_GAKUFU_H

#include "global.h"

struct EnGakufu;

typedef void (*EnGakufuActionFunc)(struct EnGakufu* this, GlobalContext* globalCtx);

typedef struct EnGakufu {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xC];
    /* 0x0150 */ EnGakufuActionFunc actionFunc;
} EnGakufu; // size = 0x154

extern const ActorInit En_Gakufu_InitVars;

#endif // Z_EN_GAKUFU_H
