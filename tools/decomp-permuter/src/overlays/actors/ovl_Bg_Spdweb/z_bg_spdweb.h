#ifndef Z_BG_SPDWEB_H
#define Z_BG_SPDWEB_H

#include <global.h>

struct BgSpdweb;

typedef struct BgSpdweb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1B8];
} BgSpdweb; // size = 0x2FC

extern const ActorInit Bg_Spdweb_InitVars;

#endif // Z_BG_SPDWEB_H
