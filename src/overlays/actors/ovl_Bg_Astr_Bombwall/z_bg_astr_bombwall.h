#ifndef Z_BG_ASTR_BOMBWALL_H
#define Z_BG_ASTR_BOMBWALL_H

#include "global.h"

struct BgAstrBombwall;

typedef void (*BgAstrBombwallActionFunc)(struct BgAstrBombwall*, GlobalContext*);
typedef struct BgAstrBombwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 unk144;                         /* inferred */
    /* 0x148 */ char pad148[0x14];                  /* maybe part of unk144[6]? */
    /* 0x15C */ BgAstrBombwallActionFunc actionFunc;
    /* 0x160 */ ColliderTris unk160;                /* inferred */
    /* 0x180 */ ColliderTrisElement unk180;         /* inferred */
    /* 0x1DC */ char pad1DC[0x5C];
    /* 0x238 */ s16 unk238;                         /* inferred */
    /* 0x23A */ char pad23A[2];
} BgAstrBombwall;
extern const ActorInit Bg_Astr_Bombwall_InitVars;

#endif // Z_BG_ASTR_BOMBWALL_H
