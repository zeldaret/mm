#ifndef Z_EN_EGOL_H
#define Z_EN_EGOL_H

#include "global.h"

struct EnEgol;

typedef struct EnEgol {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1D2C];
} EnEgol; // size = 0x1E70

extern const ActorInit En_Egol_InitVars;

#endif // Z_EN_EGOL_H
