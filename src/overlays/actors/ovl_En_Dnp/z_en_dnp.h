#ifndef _Z_EN_DNP_H_
#define _Z_EN_DNP_H_

#include <global.h>

struct EnDnp;

typedef struct EnDnp {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x200];
} EnDnp; // size = 0x344

extern const ActorInit En_Dnp_InitVars;

#endif
