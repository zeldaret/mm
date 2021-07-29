#ifndef Z_EN_RG_H
#define Z_EN_RG_H

#include "global.h"

struct EnRg;

typedef void (*EnRgActionFunc)(struct EnRg* this, GlobalContext* globalCtx);

typedef struct EnRg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnRgActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x940];
} EnRg; // size = 0xACC

extern const ActorInit En_Rg_InitVars;

#endif // Z_EN_RG_H
