#ifndef _Z_BG_ICICLE_H_
#define _Z_BG_ICICLE_H_

#include <global.h>

struct BgIcicle;

typedef struct BgIcicle {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgIcicle; // size = 0x1B0

extern const ActorInit Bg_Icicle_InitVars;

#endif
