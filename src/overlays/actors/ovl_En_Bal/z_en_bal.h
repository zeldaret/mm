#ifndef _Z_EN_BAL_H_
#define _Z_EN_BAL_H_

#include <global.h>

struct EnBal;

typedef struct EnBal {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x270];
} EnBal; // size = 0x3B4

extern const ActorInit En_Bal_InitVars;

#endif
