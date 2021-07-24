#ifndef Z_EN_COL_MAN_H
#define Z_EN_COL_MAN_H

#include "global.h"

struct EnColMan;

typedef struct EnColMan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
} EnColMan; // size = 0x1A0

extern const ActorInit En_Col_Man_InitVars;

#endif // Z_EN_COL_MAN_H
