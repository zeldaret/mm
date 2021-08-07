#ifndef Z_EN_MUSHI2_H
#define Z_EN_MUSHI2_H

#include "global.h"

struct EnMushi2;

typedef void (*EnMushi2ActionFunc)(struct EnMushi2* this, GlobalContext* globalCtx);

typedef struct EnMushi2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C4];
    /* 0x0308 */ EnMushi2ActionFunc actionFunc;
    /* 0x030C */ char unk_30C[0x68];
} EnMushi2; // size = 0x374

extern const ActorInit En_Mushi2_InitVars;

#endif // Z_EN_MUSHI2_H
