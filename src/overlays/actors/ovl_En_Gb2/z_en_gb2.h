#ifndef Z_EN_GB2_H
#define Z_EN_GB2_H

#include "global.h"

struct EnGb2;

typedef void (*EnGb2ActionFunc)(struct EnGb2* this, GlobalContext* globalCtx);

typedef struct EnGb2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xD4];
    /* 0x0218 */ EnGb2ActionFunc actionFunc;
    /* 0x021C */ char unk_21C[0x78];
} EnGb2; // size = 0x294

extern const ActorInit En_Gb2_InitVars;

#endif // Z_EN_GB2_H
