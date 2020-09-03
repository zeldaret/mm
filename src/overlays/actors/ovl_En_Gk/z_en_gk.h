#ifndef _Z_EN_GK_H_
#define _Z_EN_GK_H_

#include <global.h>

struct EnGk;

typedef struct EnGk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x214];
} EnGk; // size = 0x358

extern const ActorInit En_Gk_InitVars;

#endif
