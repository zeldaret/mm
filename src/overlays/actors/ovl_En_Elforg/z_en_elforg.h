#ifndef Z_EN_ELFORG_H
#define Z_EN_ELFORG_H

#include "global.h"

struct EnElforg;

typedef struct EnElforg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xEC];
} EnElforg; // size = 0x230

extern const ActorInit En_Elforg_InitVars;

#endif // Z_EN_ELFORG_H
