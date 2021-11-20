#ifndef Z_EN_KAME_H
#define Z_EN_KAME_H

#include "global.h"

struct EnKame;

typedef void (*EnKameActionFunc)(struct EnKame*, GlobalContext*);

typedef struct EnKame {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x154];
    /* 0x0298 */ EnKameActionFunc actionFunc;
    /* 0x029C */ char unk_29C[0xF0];
} EnKame; // size = 0x38C

extern const ActorInit En_Kame_InitVars;

#endif // Z_EN_KAME_H
