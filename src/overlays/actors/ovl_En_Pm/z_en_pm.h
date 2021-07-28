#ifndef Z_EN_PM_H
#define Z_EN_PM_H

#include "global.h"

struct EnPm;

typedef struct EnPm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x25C];
} EnPm; // size = 0x3A0

extern const ActorInit En_Pm_InitVars;

#endif // Z_EN_PM_H
