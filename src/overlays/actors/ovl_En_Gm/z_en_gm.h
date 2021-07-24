#ifndef Z_EN_GM_H
#define Z_EN_GM_H

#include "global.h"

struct EnGm;

typedef struct EnGm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C0];
} EnGm; // size = 0x404

extern const ActorInit En_Gm_InitVars;

#endif // Z_EN_GM_H
