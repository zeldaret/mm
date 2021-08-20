#ifndef Z_EN_WALLMAS_H
#define Z_EN_WALLMAS_H

#include "global.h"

struct EnWallmas;

typedef void (*EnWallmasActionFunc)(struct EnWallmas*, GlobalContext*);

typedef struct EnWallmas {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnWallmasActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x218];
} EnWallmas; // size = 0x3A4

extern const ActorInit En_Wallmas_InitVars;

#endif // Z_EN_WALLMAS_H
