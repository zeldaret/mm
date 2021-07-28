#ifndef Z_BG_IKNINSIDE_H
#define Z_BG_IKNINSIDE_H

#include "global.h"

struct BgIkninside;

typedef struct BgIkninside {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgIkninside; // size = 0x1B0

extern const ActorInit Bg_Ikninside_InitVars;

#endif // Z_BG_IKNINSIDE_H
