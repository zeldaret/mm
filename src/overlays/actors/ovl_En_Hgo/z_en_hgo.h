#ifndef _Z_EN_HGO_H_
#define _Z_EN_HGO_H_

#include <global.h>

struct EnHgo;

typedef struct EnHgo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D4];
} EnHgo; // size = 0x318

extern const ActorInit En_Hgo_InitVars;

#endif
