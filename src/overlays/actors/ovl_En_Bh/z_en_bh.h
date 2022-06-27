#ifndef Z_EN_BH_H
#define Z_EN_BH_H

#include "global.h"

struct EnBh;

typedef void (*EnBhActionFunc)(struct EnBh*, PlayState*);

typedef struct EnBh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA4];
    /* 0x1E8 */ EnBhActionFunc actionFunc;
} EnBh; // size = 0x1EC

extern const ActorInit En_Bh_InitVars;

#endif // Z_EN_BH_H
