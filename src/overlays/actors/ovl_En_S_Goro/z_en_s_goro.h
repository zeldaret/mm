#ifndef Z_EN_S_GORO_H
#define Z_EN_S_GORO_H

#include "global.h"

#define EN_S_GORO_GET_PARAM_F(thisx) ((thisx)->params & 0xF)

struct EnSGoro;

typedef void (*EnSGoroActionFunc)(struct EnSGoro*, GlobalContext*);

typedef struct EnSGoro {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x48];
    /* 0x018C */ EnSGoroActionFunc actionFunc;
    /* 0x0190 */ char unk_190[0x180];
} EnSGoro; // size = 0x310

extern const ActorInit En_S_Goro_InitVars;

#endif // Z_EN_S_GORO_H
