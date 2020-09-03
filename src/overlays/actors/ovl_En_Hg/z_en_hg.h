#ifndef Z_EN_HG_H
#define Z_EN_HG_H

#include <global.h>

struct EnHg;

typedef struct EnHg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D4];
} EnHg; // size = 0x318

extern const ActorInit En_Hg_InitVars;

#endif // Z_EN_HG_H
