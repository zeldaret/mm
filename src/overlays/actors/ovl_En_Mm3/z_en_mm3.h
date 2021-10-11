#ifndef Z_EN_MM3_H
#define Z_EN_MM3_H

#include "global.h"

struct EnMm3;

typedef void (*EnMm3ActionFunc)(struct EnMm3*, GlobalContext*);

typedef struct EnMm3 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnMm3ActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0xE0];
} EnMm3; // size = 0x2B8

extern const ActorInit En_Mm3_InitVars;

#endif // Z_EN_MM3_H
