#ifndef Z_EN_TEST4_H
#define Z_EN_TEST4_H

#include "global.h"

struct EnTest4;

typedef void (*EnTest4ActionFunc)(struct EnTest4*, GlobalContext*);

typedef struct EnTest4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xC];
    /* 0x0150 */ EnTest4ActionFunc actionFunc;
} EnTest4; // size = 0x154

extern const ActorInit En_Test4_InitVars;

#endif // Z_EN_TEST4_H
