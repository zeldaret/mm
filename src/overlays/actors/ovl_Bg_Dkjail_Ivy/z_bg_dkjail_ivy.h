#ifndef _Z_BG_DKJAIL_IVY_H_
#define _Z_BG_DKJAIL_IVY_H_

#include <global.h>

struct BgDkjailIvy;

typedef struct BgDkjailIvy {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgDkjailIvy; // size = 0x1B0

extern const ActorInit Bg_Dkjail_Ivy_InitVars;

#endif
