#ifndef _Z_EN_DY_EXTRA_H_
#define _Z_EN_DY_EXTRA_H_

#include <global.h>

struct EnDyExtra;

typedef struct EnDyExtra {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28];
} EnDyExtra; // size = 0x16C

extern const ActorInit En_Dy_Extra_InitVars;

#endif
