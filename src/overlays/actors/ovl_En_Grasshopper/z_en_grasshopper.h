#ifndef Z_EN_GRASSHOPPER_H
#define Z_EN_GRASSHOPPER_H

#include "global.h"

struct EnGrasshopper;

typedef struct EnGrasshopper {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x172C];
} EnGrasshopper; // size = 0x1870

extern const ActorInit En_Grasshopper_InitVars;

#endif // Z_EN_GRASSHOPPER_H
