#ifndef Z_EN_JG_H
#define Z_EN_JG_H

#include <global.h>

struct EnJg;

typedef struct EnJg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x290];
} EnJg; // size = 0x3D4

extern const ActorInit En_Jg_InitVars;

#endif // Z_EN_JG_H
