#ifndef Z_BG_HAKA_TOMB_H
#define Z_BG_HAKA_TOMB_H

#include <global.h>

struct BgHakaTomb;

typedef struct BgHakaTomb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} BgHakaTomb; // size = 0x164

extern const ActorInit Bg_Haka_Tomb_InitVars;

#endif // Z_BG_HAKA_TOMB_H
