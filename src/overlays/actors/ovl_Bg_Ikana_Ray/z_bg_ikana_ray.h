#ifndef Z_BG_IKANA_RAY_H
#define Z_BG_IKANA_RAY_H

#include <global.h>

struct BgIkanaRay;

typedef struct BgIkanaRay {
    /* 0x000 */ Actor base;
    /* 0x144 */ ColCylinder collision;
    /* 0x190 */ AnimatedTexture* animatedTextures;
    /* 0x194 */ void (*update)(struct BgIkanaRay*, GlobalContext*);
} BgIkanaRay; // size = 0x198

extern const ActorInit Bg_Ikana_Ray_InitVars;

#endif // Z_BG_IKANA_RAY_H
