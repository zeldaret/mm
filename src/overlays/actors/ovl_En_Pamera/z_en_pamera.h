#ifndef Z_EN_PAMERA_H
#define Z_EN_PAMERA_H

#include "global.h"

struct EnPamera;

typedef struct EnPamera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1E4];
} EnPamera; // size = 0x328

extern const ActorInit En_Pamera_InitVars;

#endif // Z_EN_PAMERA_H
