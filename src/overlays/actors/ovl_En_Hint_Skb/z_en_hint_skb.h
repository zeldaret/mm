#ifndef _Z_EN_HINT_SKB_H_
#define _Z_EN_HINT_SKB_H_

#include <global.h>

struct EnHintSkb;

typedef struct EnHintSkb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2A8];
} EnHintSkb; // size = 0x3EC

extern const ActorInit En_Hint_Skb_InitVars;

#endif
