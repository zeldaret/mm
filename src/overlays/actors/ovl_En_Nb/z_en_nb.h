#ifndef Z_EN_NB_H
#define Z_EN_NB_H

#include "global.h"

struct EnNb;

typedef void (*EnNbActionFunc)(struct EnNb*, PlayState*);

typedef struct EnNb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ EnNbActionFunc actionFunc;
    /* 0x18C */ char unk_18C[0x110];
} EnNb; // size = 0x29C

extern const ActorInit En_Nb_InitVars;

#endif // Z_EN_NB_H
