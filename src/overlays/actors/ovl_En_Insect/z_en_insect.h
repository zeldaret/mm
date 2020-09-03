#ifndef Z_EN_INSECT_H
#define Z_EN_INSECT_H

#include <global.h>

struct EnInsect;

typedef struct EnInsect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D4];
} EnInsect; // size = 0x318

extern const ActorInit En_Insect_InitVars;

#endif // Z_EN_INSECT_H
