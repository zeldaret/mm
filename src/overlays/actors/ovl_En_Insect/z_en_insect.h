#ifndef Z_EN_INSECT_H
#define Z_EN_INSECT_H

#include "global.h"

struct EnInsect;

typedef void (*EnInsectActionFunc)(struct EnInsect*, GlobalContext*);

typedef struct EnInsect {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C4];
    /* 0x0308 */ EnInsectActionFunc actionFunc;
    /* 0x030C */ char unk_30C[0xC];
} EnInsect; // size = 0x318

extern const ActorInit En_Insect_InitVars;

#endif // Z_EN_INSECT_H
