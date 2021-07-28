#ifndef Z_BG_DY_YOSEIZO_H
#define Z_BG_DY_YOSEIZO_H

#include "global.h"

struct BgDyYoseizo;

typedef struct BgDyYoseizo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x33C0];
} BgDyYoseizo; // size = 0x3504

extern const ActorInit Bg_Dy_Yoseizo_InitVars;

#endif // Z_BG_DY_YOSEIZO_H
