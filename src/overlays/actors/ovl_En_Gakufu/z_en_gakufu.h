#ifndef Z_EN_GAKUFU_H
#define Z_EN_GAKUFU_H

#include "global.h"

struct EnGakufu;

typedef void (*EnGakufuActionFunc)(struct EnGakufu*, GlobalContext*);

typedef struct EnGakufu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 songIndex;
    /* 0x148 */ u8 buttonIdx[8];
    /* 0x150 */ EnGakufuActionFunc actionFunc;
} EnGakufu; // size = 0x154

extern const ActorInit En_Gakufu_InitVars;

#endif // Z_EN_GAKUFU_H
