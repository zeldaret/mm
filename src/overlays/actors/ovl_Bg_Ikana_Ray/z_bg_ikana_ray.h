#ifndef Z_BG_IKANA_RAY_H
#define Z_BG_IKANA_RAY_H

#include "global.h"

struct BgIkanaRay;

typedef void (*BgIkanaRayActionFunc)(struct BgIkanaRay*, GlobalContext*);

typedef struct BgIkanaRay {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collision;
    /* 0x190 */ AnimatedMaterial* animatedTextures;
    /* 0x194 */ BgIkanaRayActionFunc actionFunc;
} BgIkanaRay; // size = 0x198

extern const ActorInit Bg_Ikana_Ray_InitVars;

#endif // Z_BG_IKANA_RAY_H
