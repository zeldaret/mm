#ifndef _Z_BG_GORON_OYU_H_
#define _Z_BG_GORON_OYU_H_

#include <global.h>

struct BgGoronOyu;

typedef struct BgGoronOyu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3C];
} BgGoronOyu; // size = 0x180

extern const ActorInit Bg_Goron_Oyu_InitVars;

#endif
