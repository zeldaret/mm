#ifndef Z_EN_DY_EXTRA_H
#define Z_EN_DY_EXTRA_H

#include "global.h"

struct EnDyExtra;

typedef void (*EnDyExtraActionFunc)(struct EnDyExtra*, GlobalContext*);

typedef struct EnDyExtra {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnDyExtraActionFunc actionFunc;
    /* 0x148 */ s16 type;
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ s16 unk14E;
    /* 0x150 */ f32 unk150;
    /* 0x154 */ char unk154[0xC];
    /* 0x160 */ Vec3f unk160;
} EnDyExtra; // size = 0x16C

extern const ActorInit En_Dy_Extra_InitVars;

#endif // Z_EN_DY_EXTRA_H
