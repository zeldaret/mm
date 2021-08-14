#ifndef Z_EN_ZOT_H
#define Z_EN_ZOT_H

#include "global.h"

struct EnZot;

typedef void (*EnZotActionFunc)(struct EnZot*, GlobalContext*);

typedef struct EnZot {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1B4];
    /* 0x02F8 */ EnZotActionFunc actionFunc;
} EnZot; // size = 0x2FC

extern const ActorInit En_Zot_InitVars;

#endif // Z_EN_ZOT_H
