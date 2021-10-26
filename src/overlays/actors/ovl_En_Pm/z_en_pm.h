#ifndef Z_EN_PM_H
#define Z_EN_PM_H

#include "global.h"

struct EnPm;

typedef void (*EnPmActionFunc)(struct EnPm*, GlobalContext*);

typedef struct EnPm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnPmActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x214];
} EnPm; // size = 0x3A0

extern const ActorInit En_Pm_InitVars;

#endif // Z_EN_PM_H
