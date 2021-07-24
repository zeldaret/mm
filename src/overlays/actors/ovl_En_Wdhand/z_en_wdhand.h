#ifndef Z_EN_WDHAND_H
#define Z_EN_WDHAND_H

#include "global.h"

struct EnWdhand;

typedef struct EnWdhand {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x310];
} EnWdhand; // size = 0x454

extern const ActorInit En_Wdhand_InitVars;

#endif // Z_EN_WDHAND_H
