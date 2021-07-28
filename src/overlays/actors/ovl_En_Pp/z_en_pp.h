#ifndef Z_EN_PP_H
#define Z_EN_PP_H

#include "global.h"

struct EnPp;

typedef struct EnPp {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4A8];
} EnPp; // size = 0x5EC

extern const ActorInit En_Pp_InitVars;

#endif // Z_EN_PP_H
