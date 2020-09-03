#ifndef _Z_BG_LAST_BWALL_H_
#define _Z_BG_LAST_BWALL_H_

#include <global.h>

struct BgLastBwall;

typedef struct BgLastBwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xF8];
} BgLastBwall; // size = 0x23C

extern const ActorInit Bg_Last_Bwall_InitVars;

#endif
