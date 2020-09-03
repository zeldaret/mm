#ifndef _Z_EN_GG_H_
#define _Z_EN_GG_H_

#include <global.h>

struct EnGg;

typedef struct EnGg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24C];
} EnGg; // size = 0x390

extern const ActorInit En_Gg_InitVars;

#endif
