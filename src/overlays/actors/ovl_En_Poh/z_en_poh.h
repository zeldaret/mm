#ifndef Z_EN_POH_H
#define Z_EN_POH_H

#include "global.h"

struct EnPoh;

typedef void (*EnPohActionFunc)(struct EnPoh* this, GlobalContext* globalCtx);

typedef struct EnPoh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnPohActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x28C];
} EnPoh; // size = 0x418

extern const ActorInit En_Poh_InitVars;

#endif // Z_EN_POH_H
