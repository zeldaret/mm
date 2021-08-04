#ifndef Z_EN_EGOL_H
#define Z_EN_EGOL_H

#include "global.h"

struct EnEgol;

typedef void (*EnEgolActionFunc)(struct EnEgol* this, GlobalContext* globalCtx);

typedef struct EnEgol {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x164];
    /* 0x02A8 */ EnEgolActionFunc actionFunc;
    /* 0x02AC */ char unk_2AC[0x1BC4];
} EnEgol; // size = 0x1E70

extern const ActorInit En_Egol_InitVars;

#endif // Z_EN_EGOL_H
