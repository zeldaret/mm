#ifndef Z_BG_F40_SWLIFT_H
#define Z_BG_F40_SWLIFT_H

#include "global.h"

struct BgF40Swlift;

typedef struct BgF40Swlift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} BgF40Swlift; // size = 0x160

extern const ActorInit Bg_F40_Swlift_InitVars;

#endif // Z_BG_F40_SWLIFT_H
