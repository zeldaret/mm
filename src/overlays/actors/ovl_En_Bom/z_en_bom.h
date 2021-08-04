#ifndef Z_EN_BOM_H
#define Z_EN_BOM_H

#include "global.h"

struct EnBom;

typedef void (*EnBomActionFunc)(struct EnBom* this, GlobalContext* globalCtx);

typedef struct EnBom {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xAC];
    /* 0x01F0 */ s16 timer;
    /* 0x01F2 */ char unk_1F2[0xE];
    /* 0x0200 */ EnBomActionFunc actionFunc;
} EnBom; // size = 0x204

extern const ActorInit En_Bom_InitVars;

#endif // Z_EN_BOM_H
