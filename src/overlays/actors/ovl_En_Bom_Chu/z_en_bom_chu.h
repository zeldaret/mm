#ifndef Z_EN_BOM_CHU_H
#define Z_EN_BOM_CHU_H

#include "global.h"

struct EnBomChu;

typedef struct EnBomChu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x9C];
} EnBomChu; // size = 0x1E0

extern const ActorInit En_Bom_Chu_InitVars;

#endif // Z_EN_BOM_CHU_H
