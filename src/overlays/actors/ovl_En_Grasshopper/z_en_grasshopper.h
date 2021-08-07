#ifndef Z_EN_GRASSHOPPER_H
#define Z_EN_GRASSHOPPER_H

#include "global.h"

struct EnGrasshopper;

typedef void (*EnGrasshopperActionFunc)(struct EnGrasshopper* this, GlobalContext* globalCtx);

typedef struct EnGrasshopper {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x164];
    /* 0x02A8 */ EnGrasshopperActionFunc actionFunc;
    /* 0x02AC */ char unk_2AC[0x15C4];
} EnGrasshopper; // size = 0x1870

extern const ActorInit En_Grasshopper_InitVars;

#endif // Z_EN_GRASSHOPPER_H
