#ifndef Z_EN_RAIL_SKB_H
#define Z_EN_RAIL_SKB_H

#include "global.h"

struct EnRailSkb;

typedef struct EnRailSkb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C0];
} EnRailSkb; // size = 0x404

extern const ActorInit En_Rail_Skb_InitVars;

#endif // Z_EN_RAIL_SKB_H
