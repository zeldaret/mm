#ifndef Z_EN_WIZ_FIRE_H
#define Z_EN_WIZ_FIRE_H

#include "global.h"

struct EnWizFire;

typedef void (*EnWizFireActionFunc)(struct EnWizFire*, GlobalContext*);

typedef struct EnWizFire {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnWizFireActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x29AC];
} EnWizFire; // size = 0x2AF4

extern const ActorInit En_Wiz_Fire_InitVars;

#endif // Z_EN_WIZ_FIRE_H
