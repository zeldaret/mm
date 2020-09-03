#ifndef _Z_BG_SINKAI_KABE_H_
#define _Z_BG_SINKAI_KABE_H_

#include <global.h>

struct BgSinkaiKabe;

typedef struct BgSinkaiKabe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} BgSinkaiKabe; // size = 0x170

extern const ActorInit Bg_Sinkai_Kabe_InitVars;

#endif
