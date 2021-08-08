#ifndef Z_EN_NB_H
#define Z_EN_NB_H

#include "global.h"

struct EnNb;

typedef void (*EnNbActionFunc)(struct EnNb* this, GlobalContext* globalCtx);

typedef struct EnNb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnNbActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x110];
} EnNb; // size = 0x29C

extern const ActorInit En_Nb_InitVars;

#endif // Z_EN_NB_H
