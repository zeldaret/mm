#ifndef Z_EN_SHN_H
#define Z_EN_SHN_H

#include "global.h"

struct EnShn;

typedef void (*EnShnActionFunc)(struct EnShn*, GlobalContext*);

typedef struct EnShn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnShnActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x1A8];
} EnShn; // size = 0x2F0

extern const ActorInit En_Shn_InitVars;

#endif // Z_EN_SHN_H
