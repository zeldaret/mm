#ifndef Z_EN_ANI_H
#define Z_EN_ANI_H

#include "global.h"

struct EnAni;

typedef struct EnAni {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1BC];
} EnAni; // size = 0x300

extern const ActorInit En_Ani_InitVars;

#endif // Z_EN_ANI_H
