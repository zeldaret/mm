#ifndef Z_BG_MBAR_CHAIR_H
#define Z_BG_MBAR_CHAIR_H

#include <global.h>

struct BgMbarChair;

typedef struct BgMbarChair {
    /* 0x000 */ DynaPolyActor dyna;
} BgMbarChair; // size = 0x15C

extern const ActorInit Bg_Mbar_Chair_InitVars;

#endif // Z_BG_MBAR_CHAIR_H
