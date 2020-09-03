#ifndef _Z_EN_WOOD02_H_
#define _Z_EN_WOOD02_H_

#include <global.h>

struct EnWood02;

typedef struct EnWood02 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
} EnWood02; // size = 0x1A0

extern const ActorInit En_Wood02_InitVars;

#endif
