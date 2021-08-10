#ifndef Z_EN_ENCOUNT1_H
#define Z_EN_ENCOUNT1_H

#include "global.h"

struct EnEncount1;

typedef void (*EnEncount1ActionFunc)(struct EnEncount1* this, GlobalContext* globalCtx);

typedef struct EnEncount1 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnEncount1ActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x1C];
} EnEncount1; // size = 0x164

extern const ActorInit En_Encount1_InitVars;

#endif // Z_EN_ENCOUNT1_H
