#ifndef Z_EN_RAIL_SKB_H
#define Z_EN_RAIL_SKB_H

#include "global.h"

struct EnRailSkb;

typedef void (*EnRailSkbActionFunc)(struct EnRailSkb*, GlobalContext*);

typedef struct EnRailSkb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xE4];
    /* 0x0228 */ EnRailSkbActionFunc actionFunc;
    /* 0x022C */ char unk_22C[0x1D8];
} EnRailSkb; // size = 0x404

extern const ActorInit En_Rail_Skb_InitVars;

#endif // Z_EN_RAIL_SKB_H
