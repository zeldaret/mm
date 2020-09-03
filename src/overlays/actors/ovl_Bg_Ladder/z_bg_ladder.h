#ifndef _Z_BG_LADDER_H_
#define _Z_BG_LADDER_H_

#include <global.h>

struct BgLadder;

typedef struct BgLadder {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} BgLadder; // size = 0x164

extern const ActorInit Bg_Ladder_InitVars;

#endif
