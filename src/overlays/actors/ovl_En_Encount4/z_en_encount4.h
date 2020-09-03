#ifndef _Z_EN_ENCOUNT4_H_
#define _Z_EN_ENCOUNT4_H_

#include <global.h>

struct EnEncount4;

typedef struct EnEncount4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14];
} EnEncount4; // size = 0x158

extern const ActorInit En_Encount4_InitVars;

#endif
