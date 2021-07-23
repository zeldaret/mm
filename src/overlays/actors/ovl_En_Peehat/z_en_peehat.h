#ifndef Z_EN_PEEHAT_H
#define Z_EN_PEEHAT_H

#include "global.h"

struct EnPeehat;

typedef struct EnPeehat {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3FC];
} EnPeehat; // size = 0x540

extern const ActorInit En_Peehat_InitVars;

#endif // Z_EN_PEEHAT_H
