#ifndef Z_EN_HINT_SKB_H
#define Z_EN_HINT_SKB_H

#include "global.h"

struct EnHintSkb;

typedef void (*EnHintSkbActionFunc)(struct EnHintSkb*, GlobalContext*);

typedef struct EnHintSkb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xE4];
    /* 0x0228 */ EnHintSkbActionFunc actionFunc;
    /* 0x022C */ char unk_22C[0x1C0];
} EnHintSkb; // size = 0x3EC

extern const ActorInit En_Hint_Skb_InitVars;

#endif // Z_EN_HINT_SKB_H
