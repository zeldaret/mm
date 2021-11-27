#ifndef Z_EN_BOM_CHU_H
#define Z_EN_BOM_CHU_H

#include "global.h"

struct EnBomChu;

typedef void (*EnBomChuActionFunc)(struct EnBomChu*, GlobalContext*);

typedef struct EnBomChu {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBomChuActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x98];
} EnBomChu; // size = 0x1E0

extern const ActorInit En_Bom_Chu_InitVars;

#endif // Z_EN_BOM_CHU_H
