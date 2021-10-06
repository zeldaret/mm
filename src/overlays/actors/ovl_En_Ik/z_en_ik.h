#ifndef Z_EN_IK_H
#define Z_EN_IK_H

#include "global.h"

struct EnIk;

typedef void (*EnIkActionFunc)(struct EnIk*, GlobalContext*);

typedef struct EnIk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1AC];
    /* 0x02F0 */ EnIkActionFunc actionFunc;
    /* 0x02F4 */ char unk_2F4[0x374];
} EnIk; // size = 0x668

extern const ActorInit En_Ik_InitVars;

#endif // Z_EN_IK_H
