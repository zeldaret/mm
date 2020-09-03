#ifndef _Z_EN_FU_MATO_H_
#define _Z_EN_FU_MATO_H_

#include <global.h>

struct EnFuMato;

typedef struct EnFuMato {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C8];
} EnFuMato; // size = 0x30C

extern const ActorInit En_Fu_Mato_InitVars;

#endif
