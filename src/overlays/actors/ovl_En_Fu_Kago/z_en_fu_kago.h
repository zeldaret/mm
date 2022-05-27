#ifndef Z_EN_FU_KAGO_H
#define Z_EN_FU_KAGO_H

#include "global.h"

struct EnFuKago;

typedef void (*EnFuKagoActionFunc)(struct EnFuKago*, GlobalContext*);

typedef struct EnFuKago {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ EnFuKagoActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x1DC];
    /* 0x033C */ s16 unk_33C;
} EnFuKago; // size = 0x340

extern const ActorInit En_Fu_Kago_InitVars;

#endif // Z_EN_FU_KAGO_H
