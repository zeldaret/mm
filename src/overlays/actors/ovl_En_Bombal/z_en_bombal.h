#ifndef Z_EN_BOMBAL_H
#define Z_EN_BOMBAL_H

#include "global.h"

struct EnBombal;

typedef void (*EnBombalActionFunc)(struct EnBombal*, GlobalContext*);

typedef struct EnBombal {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBombalActionFunc actionFunc;
    /* 0x0148 */ char unk148[0x4];
    /* 0x014C */ s16 unk_14C;
    /* 0x0150 */ f32 unk_150;
    /* 0x0154 */ char unk154[0x150];
    /* 0x02A4 */ Vec3f unk_2A4;
    /* 0x02B0 */ char unk2B0[0x2794];
} EnBombal; // size = 0x2A44

extern const ActorInit En_Bombal_InitVars;

#endif // Z_EN_BOMBAL_H
