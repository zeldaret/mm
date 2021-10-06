#ifndef Z_BG_CRACE_MOVEBG_H
#define Z_BG_CRACE_MOVEBG_H

#include "global.h"

struct BgCraceMovebg;

typedef void (*BgCraceMovebgActionFunc)(struct BgCraceMovebg*, GlobalContext*);

typedef struct BgCraceMovebg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgCraceMovebgActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x10];
    /* 0x0170 */ s32 unk_170;
    /* 0x0174 */ char unk_174[0x20];
} BgCraceMovebg; // size = 0x194

extern const ActorInit Bg_Crace_Movebg_InitVars;

#endif // Z_BG_CRACE_MOVEBG_H
