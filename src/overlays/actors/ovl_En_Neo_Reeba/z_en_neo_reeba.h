#ifndef _Z_EN_NEO_REEBA_H_
#define _Z_EN_NEO_REEBA_H_

#include <global.h>

struct EnNeoReeba;

typedef struct EnNeoReeba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D0];
} EnNeoReeba; // size = 0x314

extern const ActorInit En_Neo_Reeba_InitVars;

#endif
