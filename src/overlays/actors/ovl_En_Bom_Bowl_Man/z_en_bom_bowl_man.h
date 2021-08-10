#ifndef Z_EN_BOM_BOWL_MAN_H
#define Z_EN_BOM_BOWL_MAN_H

#include "global.h"

struct EnBomBowlMan;

typedef void (*EnBomBowlManActionFunc)(struct EnBomBowlMan* this, GlobalContext* globalCtx);

typedef struct EnBomBowlMan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnBomBowlManActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0x74];
} EnBomBowlMan; // size = 0x2FC

extern const ActorInit En_Bom_Bowl_Man_InitVars;

#endif // Z_EN_BOM_BOWL_MAN_H
