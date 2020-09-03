#ifndef _Z_BG_BREAKWALL_H_
#define _Z_BG_BREAKWALL_H_

#include <global.h>

struct BgBreakwall;

typedef struct BgBreakwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} BgBreakwall; // size = 0x164

extern const ActorInit Bg_Breakwall_InitVars;

#endif
