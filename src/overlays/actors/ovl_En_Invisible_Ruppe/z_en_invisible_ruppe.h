#ifndef Z_EN_INVISIBLE_RUPPE_H
#define Z_EN_INVISIBLE_RUPPE_H

#include "global.h"

struct EnInvisibleRuppe;

typedef struct EnInvisibleRuppe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnInvisibleRuppe; // size = 0x198

extern const ActorInit En_Invisible_Ruppe_InitVars;

#endif // Z_EN_INVISIBLE_RUPPE_H
