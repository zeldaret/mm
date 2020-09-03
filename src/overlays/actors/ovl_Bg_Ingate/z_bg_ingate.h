#ifndef _Z_BG_INGATE_H_
#define _Z_BG_INGATE_H_

#include <global.h>

struct BgIngate;

typedef struct BgIngate {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4C];
} BgIngate; // size = 0x190

extern const ActorInit Bg_Ingate_InitVars;

#endif
