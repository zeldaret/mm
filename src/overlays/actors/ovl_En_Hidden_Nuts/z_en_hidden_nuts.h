#ifndef _Z_EN_HIDDEN_NUTS_H_
#define _Z_EN_HIDDEN_NUTS_H_

#include <global.h>

struct EnHiddenNuts;

typedef struct EnHiddenNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x13C];
} EnHiddenNuts; // size = 0x280

extern const ActorInit En_Hidden_Nuts_InitVars;

#endif
