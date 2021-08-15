#ifndef Z_ARROW_LIGHT_H
#define Z_ARROW_LIGHT_H

#include "global.h"

struct ArrowLight;

typedef void (*ArrowLightActionFunc)(struct ArrowLight*, GlobalContext*);

typedef struct ArrowLight {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ ArrowLightActionFunc actionFunc;
} ArrowLight; // size = 0x164

extern const ActorInit Arrow_Light_InitVars;

#endif // Z_ARROW_LIGHT_H
