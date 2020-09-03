#ifndef _Z_EN_GOROIWA_H_
#define _Z_EN_GOROIWA_H_

#include <global.h>

struct EnGoroiwa;

typedef struct EnGoroiwa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x108];
} EnGoroiwa; // size = 0x24C

extern const ActorInit En_Goroiwa_InitVars;

#endif
