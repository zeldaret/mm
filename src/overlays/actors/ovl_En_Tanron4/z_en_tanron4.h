#ifndef Z_EN_TANRON4_H
#define Z_EN_TANRON4_H

#include "global.h"

struct EnTanron4;

typedef void (*EnTanron4ActionFunc)(struct EnTanron4*, GlobalContext*);

typedef struct EnTanron4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xE8];
    /* 0x022C */ EnTanron4ActionFunc actionFunc;
} EnTanron4; // size = 0x230

extern const ActorInit En_Tanron4_InitVars;

#endif // Z_EN_TANRON4_H
