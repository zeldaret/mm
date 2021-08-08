#ifndef Z_EN_BOMBERS2_H
#define Z_EN_BOMBERS2_H

#include "global.h"

struct EnBombers2;

typedef void (*EnBombers2ActionFunc)(struct EnBombers2* this, GlobalContext* globalCtx);

typedef struct EnBombers2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnBombers2ActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0x94];
} EnBombers2; // size = 0x31C

extern const ActorInit En_Bombers2_InitVars;

#endif // Z_EN_BOMBERS2_H
