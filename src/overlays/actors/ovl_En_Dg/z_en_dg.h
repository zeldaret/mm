#ifndef _Z_EN_DG_H_
#define _Z_EN_DG_H_

#include <global.h>

struct EnDg;

typedef struct EnDg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x15C];
} EnDg; // size = 0x2A0

extern const ActorInit En_Dg_InitVars;

#endif
