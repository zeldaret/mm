#ifndef Z_BG_HAKUGIN_BOMBWALL_H
#define Z_BG_HAKUGIN_BOMBWALL_H

#include "global.h"

struct BgHakuginBombwall;

typedef void (*BgHakuginBombwallActionFunc)(struct BgHakuginBombwall*, GlobalContext*);
typedef s32 (*BgHakuginBombwallUnkFunc)(Actor*, GlobalContext*);
typedef void (*BgHakuginBombwallUnkFunc2)(struct BgHakuginBombwall*, GlobalContext*);

#define BGHAKUGIN_BOMBWALL_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)
#define BGHAKUGIN_BOMBWALL_100(thisx) (((thisx)->params >> 8) & 1)

typedef struct BgHakuginBombwall {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderCylinder collider;
    /* 0x1A8 */ BgHakuginBombwallActionFunc actionFunc;
    /* 0x1AC */ s32 unk_1AC;
} BgHakuginBombwall; // size = 0x1B0

extern const ActorInit Bg_Hakugin_Bombwall_InitVars;

#endif // Z_BG_HAKUGIN_BOMBWALL_H
