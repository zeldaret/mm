#ifndef _Z_BG_DBLUE_MOVEBG_H_
#define _Z_BG_DBLUE_MOVEBG_H_

#include <global.h>

struct BgDblueMovebg;

typedef struct BgDblueMovebg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x22C];
} BgDblueMovebg; // size = 0x370

extern const ActorInit Bg_Dblue_Movebg_InitVars;

#endif
