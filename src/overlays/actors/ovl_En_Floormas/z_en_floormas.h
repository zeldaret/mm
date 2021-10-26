#ifndef Z_EN_FLOORMAS_H
#define Z_EN_FLOORMAS_H

#include "global.h"

struct EnFloormas;

typedef void (*EnFloormasActionFunc)(struct EnFloormas*, GlobalContext*);

typedef struct EnFloormas {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnFloormasActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x214];
} EnFloormas; // size = 0x3A0

extern const ActorInit En_Floormas_InitVars;

#endif // Z_EN_FLOORMAS_H
