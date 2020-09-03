#ifndef _Z_EN_RR_H_
#define _Z_EN_RR_H_

#include <global.h>

struct EnRr;

typedef struct EnRr {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x280];
} EnRr; // size = 0x3C4

extern const ActorInit En_Rr_InitVars;

#endif
