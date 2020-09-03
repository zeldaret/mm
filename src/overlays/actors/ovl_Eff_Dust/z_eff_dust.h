#ifndef _Z_EFF_DUST_H_
#define _Z_EFF_DUST_H_

#include <global.h>

struct EffDust;

typedef struct EffDust {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x41C];
} EffDust; // size = 0x560

extern const ActorInit Eff_Dust_InitVars;

#endif
