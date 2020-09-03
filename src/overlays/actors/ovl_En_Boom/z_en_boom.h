#ifndef _Z_EN_BOOM_H_
#define _Z_EN_BOOM_H_

#include <global.h>

struct EnBoom;

typedef struct EnBoom {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xB0];
} EnBoom; // size = 0x1F4

extern const ActorInit En_Boom_InitVars;

#endif
