#ifndef Z_EN_DNH_H
#define Z_EN_DNH_H

#include "global.h"

struct EnDnh;

typedef struct EnDnh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x78];
} EnDnh; // size = 0x1BC

extern const ActorInit En_Dnh_InitVars;

#endif // Z_EN_DNH_H
