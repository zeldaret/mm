#ifndef _Z_EN_HOLL_H_
#define _Z_EN_HOLL_H_

#include <global.h>

struct EnHoll;

typedef struct EnHoll {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} EnHoll; // size = 0x14C

extern const ActorInit En_Holl_InitVars;

#endif
