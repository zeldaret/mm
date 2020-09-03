#ifndef _Z_EN_LIGHT_H_
#define _Z_EN_LIGHT_H_

#include <global.h>

struct EnLight;

typedef struct EnLight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} EnLight; // size = 0x15C

extern const ActorInit En_Light_InitVars;

#endif
