#ifndef _Z_EN_NUTSBALL_H_
#define _Z_EN_NUTSBALL_H_

#include <global.h>

struct EnNutsball;

typedef struct EnNutsball {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} EnNutsball; // size = 0x194

extern const ActorInit En_Nutsball_InitVars;

#endif
