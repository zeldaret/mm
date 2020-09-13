#ifndef Z_EN_RG_H
#define Z_EN_RG_H

#include <global.h>

struct EnRg;

typedef struct EnRg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x988];
} EnRg; // size = 0xACC

extern const ActorInit En_Rg_InitVars;

#endif // Z_EN_RG_H
