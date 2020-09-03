#ifndef _Z_ARROW_LIGHT_H_
#define _Z_ARROW_LIGHT_H_

#include <global.h>

struct ArrowLight;

typedef struct ArrowLight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} ArrowLight; // size = 0x164

extern const ActorInit Arrow_Light_InitVars;

#endif
