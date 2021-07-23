#ifndef Z_EN_HINT_SKB_H
#define Z_EN_HINT_SKB_H

#include "global.h"

struct EnHintSkb;

typedef struct EnHintSkb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2A8];
} EnHintSkb; // size = 0x3EC

extern const ActorInit En_Hint_Skb_InitVars;

#endif // Z_EN_HINT_SKB_H
