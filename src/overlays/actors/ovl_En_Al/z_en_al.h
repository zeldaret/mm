#ifndef _Z_EN_AL_H_
#define _Z_EN_AL_H_

#include <global.h>

struct EnAl;

typedef struct EnAl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3BC];
} EnAl; // size = 0x500

extern const ActorInit En_Al_InitVars;

#endif
