#ifndef _Z_EN_KBT_H_
#define _Z_EN_KBT_H_

#include <global.h>

struct EnKbt;

typedef struct EnKbt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x148];
} EnKbt; // size = 0x28C

extern const ActorInit En_Kbt_InitVars;

#endif
