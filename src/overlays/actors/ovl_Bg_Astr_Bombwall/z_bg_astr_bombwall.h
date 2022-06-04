#ifndef Z_BG_ASTR_BOMBWALL_H
#define Z_BG_ASTR_BOMBWALL_H

#include "global.h"

struct BgAstrBombwall;

typedef void (*BgAstrBombwallActionFunc)(struct BgAstrBombwall*, GlobalContext*);
typedef struct BgAstrBombwall {
   /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgAstrBombwallActionFunc actionFunc;
    /* 0x160 */ ColliderTris collider;
    /* 0x180 */ ColliderTrisElement colliderElements;
    /* 0x1DC */ UNK_TYPE1 pad1DC[0x5C];
    /* 0x238 */ s16 unk238;
    /* 0x23A */ UNK_TYPE1 pad23A[2];
} BgAstrBombwall;
extern const ActorInit Bg_Astr_Bombwall_InitVars;

#endif // Z_BG_ASTR_BOMBWALL_H
