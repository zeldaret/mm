#ifndef Z_EN_DNP_H
#define Z_EN_DNP_H

#include "global.h"

struct EnDnp;

typedef struct EnDnp {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x200];
} EnDnp; // size = 0x344

extern const ActorInit En_Dnp_InitVars;

#endif // Z_EN_DNP_H
