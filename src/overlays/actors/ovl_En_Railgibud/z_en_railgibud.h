#ifndef Z_EN_RAILGIBUD_H
#define Z_EN_RAILGIBUD_H

#include "global.h"

struct EnRailgibud;

typedef struct EnRailgibud {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C4];
} EnRailgibud; // size = 0x408

extern const ActorInit En_Railgibud_InitVars;

#endif // Z_EN_RAILGIBUD_H
