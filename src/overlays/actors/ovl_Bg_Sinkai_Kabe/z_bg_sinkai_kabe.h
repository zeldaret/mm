#ifndef Z_BG_SINKAI_KABE_H
#define Z_BG_SINKAI_KABE_H

#include "global.h"

struct BgSinkaiKabe;

typedef struct BgSinkaiKabe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} BgSinkaiKabe; // size = 0x170

extern const ActorInit Bg_Sinkai_Kabe_InitVars;

#endif // Z_BG_SINKAI_KABE_H
