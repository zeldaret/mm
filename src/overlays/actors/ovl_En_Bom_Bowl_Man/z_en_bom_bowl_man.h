#ifndef _Z_EN_BOM_BOWL_MAN_H_
#define _Z_EN_BOM_BOWL_MAN_H_

#include <global.h>

struct EnBomBowlMan;

typedef struct EnBomBowlMan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1B8];
} EnBomBowlMan; // size = 0x2FC

extern const ActorInit En_Bom_Bowl_Man_InitVars;

#endif
