#ifndef Z_EN_BOMJIMB_H
#define Z_EN_BOMJIMB_H

#include "global.h"

struct EnBomjimb;

typedef void (*EnBomjimbActionFunc)(struct EnBomjimb* this, GlobalContext* globalCtx);

typedef struct EnBomjimb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnBomjimbActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0xAC];
} EnBomjimb; // size = 0x334

extern const ActorInit En_Bomjimb_InitVars;

#endif // Z_EN_BOMJIMB_H
