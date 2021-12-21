#ifndef Z_EN_BAT_H
#define Z_EN_BAT_H

#include "global.h"

struct EnBat;

typedef void (*EnBatActionFunc)(struct EnBat*, GlobalContext*);

typedef struct EnBat {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBatActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x94];
} EnBat; // size = 0x1DC

extern const ActorInit En_Bat_InitVars;

#endif // Z_EN_BAT_H
