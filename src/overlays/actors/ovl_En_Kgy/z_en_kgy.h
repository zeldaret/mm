#ifndef _Z_EN_KGY_H_
#define _Z_EN_KGY_H_

#include <global.h>

struct EnKgy;

typedef struct EnKgy {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C4];
} EnKgy; // size = 0x308

extern const ActorInit En_Kgy_InitVars;

#endif
