#ifndef Z_EN_SKB_H
#define Z_EN_SKB_H

#include "global.h"

struct EnSkb;

typedef void (*EnSkbActionFunc)(struct EnSkb* this, GlobalContext* globalCtx);

typedef struct EnSkb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xE4];
    /* 0x0228 */ EnSkbActionFunc actionFunc;
    /* 0x022C */ char unk_22C[0x1BC];
} EnSkb; // size = 0x3E8

extern const ActorInit En_Skb_InitVars;

#endif // Z_EN_SKB_H
