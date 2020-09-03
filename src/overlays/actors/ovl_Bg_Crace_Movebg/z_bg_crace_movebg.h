#ifndef _Z_BG_CRACE_MOVEBG_H_
#define _Z_BG_CRACE_MOVEBG_H_

#include <global.h>

struct BgCraceMovebg;

typedef struct BgCraceMovebg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} BgCraceMovebg; // size = 0x194

extern const ActorInit Bg_Crace_Movebg_InitVars;

#endif
