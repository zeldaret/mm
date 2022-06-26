#ifndef Z_BG_IKANA_MIRROR_H
#define Z_BG_IKANA_MIRROR_H

#include "global.h"

struct BgIkanaMirror;

typedef void (*BgIkanaMirrorActionFunc)(struct BgIkanaMirror*, GlobalContext*);

typedef struct BgIkanaMirror {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderTris colliderTris;
    /* 0x17C */ ColliderTrisElement colliderTrisElements[9];
    /* 0x4B8 */ ColliderQuad colliderQuad[2];
    /* 0x5B8 */ BgIkanaMirrorActionFunc actionFunc;
    /* 0x5BC */ AnimatedMaterial* lightAbsorptionTexture;
    /* 0x5C0 */ AnimatedMaterial* lightEmissionTexture;
    /* 0x5C4 */ s16 timer;
    /* 0x5C6 */ u8 lightAbsorptionAlpha;
    /* 0x5C7 */ u8 lightEmissionAlpha;
    /* 0x5C8 */ s8 isEmittingLight;
} BgIkanaMirror; /* size = 0x5CC */

#endif // Z_BG_IKANA_MIRROR_H
