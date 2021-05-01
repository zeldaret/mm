#ifndef Z_BG_LBFSHOT_H
#define Z_BG_LBFSHOT_H

#include <global.h>

struct BgLbfshot;

typedef struct BgLbfshot {
    /* 0x000 */ DynaPolyActor dyna;
} BgLbfshot; // size = 0x160

extern const ActorInit Bg_Lbfshot_InitVars;

#endif // Z_BG_LBFSHOT_H
