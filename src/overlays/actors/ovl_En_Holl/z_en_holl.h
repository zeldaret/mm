#ifndef Z_EN_HOLL_H
#define Z_EN_HOLL_H

#include <global.h>

struct EnHoll;

typedef struct EnHoll {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} EnHoll; // size = 0x14C

extern const ActorInit En_Holl_InitVars;

#endif // Z_EN_HOLL_H
