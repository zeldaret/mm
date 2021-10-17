#ifndef Z_EN_SELLNUTS_H
#define Z_EN_SELLNUTS_H

#include <global.h>

struct EnSellnuts;

typedef struct EnSellnuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x234];
} EnSellnuts; // size = 0x378

extern const ActorInit En_Sellnuts_InitVars;

#endif // Z_EN_SELLNUTS_H
