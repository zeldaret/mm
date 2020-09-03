#ifndef _Z_BOSS_02_H_
#define _Z_BOSS_02_H_

#include <global.h>

struct Boss02;

typedef struct Boss02 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1C3C];
} Boss02; // size = 0x1D80

extern const ActorInit Boss_02_InitVars;

#endif
