#ifndef Z_BG_IKANA_MIRROR_H
#define Z_BG_IKANA_MIRROR_H

#include "global.h"

struct BgIkanaMirror;

typedef void (*BgIkanaMirrorActionFunc)(struct BgIkanaMirror*, GlobalContext*);

// must dyna Actor field.
typedef struct BgIkanaMirror {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderTris colliderTris;
    /* 0x17C */ ColliderTrisElement colliderTrisElements[9];
    /* 0x4B8 */ ColliderQuad colliderQuad[2];
    /* 0x5B8 */ BgIkanaMirrorActionFunc actionFunc;
    /* 0x5BC */ AnimatedMaterial* emittingLightTexture;
    /* 0x5C0 */ AnimatedMaterial* absorbingLightTexture; // absorbing light
    /* 0x5C4 */ s16 timer;                               // probably charge counter for light
    /* 0x5C6 */ u8 unk5C6;                               // positive means absorbing light/load absorb light material
    /* 0x5C7 */ u8 unk5C7; // positive means "was" (?) emitting light or can load light emission
    /* 0x5C8 */ s8 unk5C8; // boolean for isEmittingLight
    /* 0x5C9 */ char pad5C9[3];
} BgIkanaMirror; /* size = 0x5CC */

#endif // Z_BG_IKANA_MIRROR_H
