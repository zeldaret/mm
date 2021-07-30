#ifndef Z_BG_CRACE_MOVEBG_H
#define Z_BG_CRACE_MOVEBG_H

#include "global.h"

struct BgCraceMovebg;

typedef void (*BgCraceMovebgActionFunc)(struct BgCraceMovebg* this, GlobalContext* globalCtx);

typedef struct BgCraceMovebg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
    /* 0x170 */ s32 unk_170;
    /* 0x174 */ char unk_174[0x20];
} BgCraceMovebg; // size = 0x194

extern const ActorInit Bg_Crace_Movebg_InitVars;

#endif // Z_BG_CRACE_MOVEBG_H
