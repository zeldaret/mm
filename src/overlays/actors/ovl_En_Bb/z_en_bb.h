#ifndef _Z_EN_BB_H_
#define _Z_EN_BB_H_

#include <global.h>

struct EnBb;

typedef struct EnBb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x208];
} EnBb; // size = 0x34C

extern const ActorInit En_Bb_InitVars;

#endif
