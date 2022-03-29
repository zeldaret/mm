#ifndef Z_BG_BREAKWALL_H
#define Z_BG_BREAKWALL_H

#include "global.h"

struct BgBreakwall;

typedef void (*BgBreakwallActionFunc)(struct BgBreakwall*, GlobalContext*);
typedef s32 (*BgBreakwallUnkFunc)(struct BgBreakwall*, GlobalContext*);
typedef void (*BgBreakwallUnkFunc2)(struct BgBreakwall*, GlobalContext*);

#define BGBREAKWALL_GET_F(thisx) ((thisx)-> params & 0xF)
#define BGBREAKWALL_SWITCHFLAG(thisx) (((thisx)-> params & 0xFE00) >> 9)

enum {
    /*  7 */ BGBREAKWALL_F_7 = 7,
    /*  9 */ BGBREAKWALL_F_9 = 9,
    /* 11 */ BGBREAKWALL_F_11 = 11,
};

typedef struct BgBreakwall {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ s8 unk_15C;
    /* 0x015D */ u8 switchFlag;
    /* 0x015E */ u8 unk_15E;
    /* 0x0160 */ BgBreakwallActionFunc actionFunc;
} BgBreakwall; // size = 0x164

extern const ActorInit Bg_Breakwall_InitVars;

#endif // Z_BG_BREAKWALL_H
