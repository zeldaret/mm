#ifndef Z_EN_SKB_H
#define Z_EN_SKB_H

#include "global.h"

struct EnSkb;

typedef struct EnSkb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2A4];
} EnSkb; // size = 0x3E8

extern const ActorInit En_Skb_InitVars;

#endif // Z_EN_SKB_H
