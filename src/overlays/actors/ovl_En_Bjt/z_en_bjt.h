#ifndef Z_EN_BJT_H
#define Z_EN_BJT_H

#include "global.h"

struct EnBjt;

typedef void (*EnBjtActionFunc)(struct EnBjt* this, GlobalContext* globalCtx);

typedef struct EnBjt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnBjtActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0xD0];
} EnBjt; // size = 0x25C

extern const ActorInit En_Bjt_InitVars;

#endif // Z_EN_BJT_H
