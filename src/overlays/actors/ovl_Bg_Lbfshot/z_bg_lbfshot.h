#ifndef Z_BG_LBFSHOT_H
#define Z_BG_LBFSHOT_H

#include <global.h>

struct BgLbfshot;

typedef struct BgLbfshot {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} BgLbfshot; // size = 0x160

extern const ActorInit Bg_Lbfshot_InitVars;

#endif // Z_BG_LBFSHOT_H
