#ifndef Z_BG_F40_FLIFT_H
#define Z_BG_F40_FLIFT_H

#include "global.h"

struct BgF40Flift;

typedef struct BgF40Flift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} BgF40Flift; // size = 0x164

extern const ActorInit Bg_F40_Flift_InitVars;

#endif // Z_BG_F40_FLIFT_H
