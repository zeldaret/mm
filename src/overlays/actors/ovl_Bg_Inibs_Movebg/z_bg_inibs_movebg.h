#ifndef _Z_BG_INIBS_MOVEBG_H_
#define _Z_BG_INIBS_MOVEBG_H_

#include <global.h>

struct BgInibsMovebg;

typedef struct BgInibsMovebg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} BgInibsMovebg; // size = 0x168

extern const ActorInit Bg_Inibs_Movebg_InitVars;

#endif
