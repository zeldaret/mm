#ifndef _Z_EN_GAKUFU_H_
#define _Z_EN_GAKUFU_H_

#include <global.h>

struct EnGakufu;

typedef struct EnGakufu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10];
} EnGakufu; // size = 0x154

extern const ActorInit En_Gakufu_InitVars;

#endif
