#ifndef Z_BG_BOTIHASIRA_H
#define Z_BG_BOTIHASIRA_H

#include "global.h"

struct BgBotihasira;

typedef struct BgBotihasira {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x68];
} BgBotihasira; // size = 0x1AC

extern const ActorInit Bg_Botihasira_InitVars;

#endif // Z_BG_BOTIHASIRA_H
