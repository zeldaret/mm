#ifndef Z_BG_FU_MIZU_H
#define Z_BG_FU_MIZU_H

#include <global.h>

struct BgFuMizu;

typedef struct BgFuMizu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} BgFuMizu; // size = 0x164

extern const ActorInit Bg_Fu_Mizu_InitVars;

#endif // Z_BG_FU_MIZU_H
