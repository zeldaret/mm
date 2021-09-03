#ifndef Z_EN_RAILGIBUD_H
#define Z_EN_RAILGIBUD_H

#include "global.h"

struct EnRailgibud;

typedef void (*EnRailgibudActionFunc)(struct EnRailgibud*, GlobalContext*);

typedef struct EnRailgibud {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnRailgibudActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x230];
} EnRailgibud; // size = 0x408

extern const ActorInit En_Railgibud_InitVars;

#endif // Z_EN_RAILGIBUD_H
