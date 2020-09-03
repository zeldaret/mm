#ifndef _Z_BG_IKANA_DHARMA_H_
#define _Z_BG_IKANA_DHARMA_H_

#include <global.h>

struct BgIkanaDharma;

typedef struct BgIkanaDharma {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgIkanaDharma; // size = 0x1B0

extern const ActorInit Bg_Ikana_Dharma_InitVars;

#endif
