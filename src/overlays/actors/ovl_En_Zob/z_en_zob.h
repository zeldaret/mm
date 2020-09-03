#ifndef _Z_EN_ZOB_H_
#define _Z_EN_ZOB_H_

#include <global.h>

struct EnZob;

typedef struct EnZob {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D4];
} EnZob; // size = 0x318

extern const ActorInit En_Zob_InitVars;

#endif
