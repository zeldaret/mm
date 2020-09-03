#ifndef _Z_EN_SKB_H_
#define _Z_EN_SKB_H_

#include <global.h>

struct EnSkb;

typedef struct EnSkb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2A4];
} EnSkb; // size = 0x3E8

extern const ActorInit En_Skb_InitVars;

#endif
