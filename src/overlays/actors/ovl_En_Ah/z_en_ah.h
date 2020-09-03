#ifndef _Z_EN_AH_H_
#define _Z_EN_AH_H_

#include <global.h>

struct EnAh;

typedef struct EnAh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C0];
} EnAh; // size = 0x304

extern const ActorInit En_Ah_InitVars;

#endif
