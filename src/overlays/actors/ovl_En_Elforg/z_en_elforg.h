#ifndef _Z_EN_ELFORG_H_
#define _Z_EN_ELFORG_H_

#include <global.h>

struct EnElforg;

typedef struct EnElforg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xEC];
} EnElforg; // size = 0x230

extern const ActorInit En_Elforg_InitVars;

#endif
