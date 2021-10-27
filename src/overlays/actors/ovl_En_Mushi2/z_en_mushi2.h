#ifndef Z_EN_MUSHI2_H
#define Z_EN_MUSHI2_H

#include "global.h"

struct EnMushi2;

typedef void (*EnMushi2ActionFunc)(struct EnMushi2*, GlobalContext*);

typedef struct EnMushi2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x133];
    /* 0x0277 */ s8 unk_277;
    /* 0x0278 */ char unk_278[0x90];
    /* 0x0308 */ EnMushi2ActionFunc actionFunc;
    /* 0x030C */ s32 unk_30C;
    /* 0x0310 */ char unk_310[0x64];
} EnMushi2; // size = 0x374

extern const ActorInit En_Mushi2_InitVars;

#endif // Z_EN_MUSHI2_H
