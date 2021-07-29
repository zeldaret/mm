#ifndef Z_EN_IG_H
#define Z_EN_IG_H

#include "global.h"

struct EnIg;

typedef void (*EnIgActionFunc)(struct EnIg* this, GlobalContext* globalCtx);

typedef struct EnIg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnIgActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x280];
} EnIg; // size = 0x40C

extern const ActorInit En_Ig_InitVars;

#endif // Z_EN_IG_H
