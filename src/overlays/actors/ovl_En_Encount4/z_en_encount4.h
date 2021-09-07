#ifndef Z_EN_ENCOUNT4_H
#define Z_EN_ENCOUNT4_H

#include "global.h"

struct EnEncount4;

typedef void (*EnEncount4ActionFunc)(struct EnEncount4*, GlobalContext*);

typedef struct EnEncount4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnEncount4ActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x10];
} EnEncount4; // size = 0x158

extern const ActorInit En_Encount4_InitVars;

#endif // Z_EN_ENCOUNT4_H
