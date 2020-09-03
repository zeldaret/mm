#ifndef Z_BG_IKANA_MIRROR_H
#define Z_BG_IKANA_MIRROR_H

#include <global.h>

struct BgIkanaMirror;

typedef struct BgIkanaMirror {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x488];
} BgIkanaMirror; // size = 0x5CC

extern const ActorInit Bg_Ikana_Mirror_InitVars;

#endif // Z_BG_IKANA_MIRROR_H
