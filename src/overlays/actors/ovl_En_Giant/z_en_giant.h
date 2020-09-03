#ifndef _Z_EN_GIANT_H_
#define _Z_EN_GIANT_H_

#include <global.h>

struct EnGiant;

typedef struct EnGiant {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x158];
} EnGiant; // size = 0x29C

extern const ActorInit En_Giant_InitVars;

#endif
