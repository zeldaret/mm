#ifndef Z_EN_BOM_H
#define Z_EN_BOM_H

#include <global.h>

struct EnBom;

typedef struct EnBom {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xAC];
    /* 0x1F0 */ s16 timer;
    /* 0x1F2 */ char unk_1F2[0x12];
} EnBom; // size = 0x204

extern const ActorInit En_Bom_InitVars;

#endif // Z_EN_BOM_H
