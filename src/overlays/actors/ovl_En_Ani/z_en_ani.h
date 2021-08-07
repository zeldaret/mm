#ifndef Z_EN_ANI_H
#define Z_EN_ANI_H

#include "global.h"

struct EnAni;

typedef void (*EnAniActionFunc)(struct EnAni* this, GlobalContext* globalCtx);

typedef struct EnAni {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1B0];
    /* 0x02F4 */ EnAniActionFunc actionFunc;
    /* 0x02F8 */ char unk_2F8[0x8];
} EnAni; // size = 0x300

extern const ActorInit En_Ani_InitVars;

#endif // Z_EN_ANI_H
