#ifndef _Z_EN_S_GORO_H_
#define _Z_EN_S_GORO_H_

#include <global.h>

struct EnSGoro;

typedef struct EnSGoro {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1CC];
} EnSGoro; // size = 0x310

extern const ActorInit En_S_Goro_InitVars;

#endif
