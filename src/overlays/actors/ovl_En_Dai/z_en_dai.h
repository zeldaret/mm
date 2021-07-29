#ifndef Z_EN_DAI_H
#define Z_EN_DAI_H

#include "global.h"

struct EnDai;

typedef void (*EnDaiActionFunc)(struct EnDai* this, GlobalContext* globalCtx);

typedef struct EnDai {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDaiActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x8E8];
} EnDai; // size = 0xA74

extern const ActorInit En_Dai_InitVars;

#endif // Z_EN_DAI_H
