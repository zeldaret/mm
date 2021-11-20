#ifndef Z_EN_PR2_H
#define Z_EN_PR2_H

#include "global.h"

struct EnPr2;

typedef void (*EnPr2ActionFunc)(struct EnPr2*, GlobalContext*);

typedef struct EnPr2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x80];
    /* 0x01C4 */ EnPr2ActionFunc actionFunc;
    /* 0x01C8 */ char unk_1C8[0x100];
} EnPr2; // size = 0x2C8

extern const ActorInit En_Pr2_InitVars;

#endif // Z_EN_PR2_H
