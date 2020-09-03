#ifndef _Z_EN_FAMOS_H_
#define _Z_EN_FAMOS_H_

#include <global.h>

struct EnFamos;

typedef struct EnFamos {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4D0];
} EnFamos; // size = 0x614

extern const ActorInit En_Famos_InitVars;

#endif
