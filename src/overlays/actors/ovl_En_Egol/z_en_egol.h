#ifndef _Z_EN_EGOL_H_
#define _Z_EN_EGOL_H_

#include <global.h>

struct EnEgol;

typedef struct EnEgol {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1D2C];
} EnEgol; // size = 0x1E70

extern const ActorInit En_Egol_InitVars;

#endif
