#ifndef _Z_BG_DANPEI_MOVEBG_H_
#define _Z_BG_DANPEI_MOVEBG_H_

#include <global.h>

struct BgDanpeiMovebg;

typedef struct BgDanpeiMovebg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x94];
} BgDanpeiMovebg; // size = 0x1D8

extern const ActorInit Bg_Danpei_Movebg_InitVars;

#endif
