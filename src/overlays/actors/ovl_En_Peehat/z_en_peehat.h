#ifndef Z_EN_PEEHAT_H
#define Z_EN_PEEHAT_H

#include "global.h"

struct EnPeehat;

typedef void (*EnPeehatActionFunc)(struct EnPeehat*, GlobalContext*);

typedef struct EnPeehat {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x164];
    /* 0x02A8 */ EnPeehatActionFunc actionFunc;
    /* 0x02AC */ char unk_2AC[0x294];
} EnPeehat; // size = 0x540

extern const ActorInit En_Peehat_InitVars;

#endif // Z_EN_PEEHAT_H
