#ifndef Z_EN_OSK_H
#define Z_EN_OSK_H

#include "global.h"

struct EnOsk;

typedef void (*EnOskActionFunc)(struct EnOsk* this, GlobalContext* globalCtx);

typedef struct EnOsk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x11C];
    /* 0x0260 */ EnOskActionFunc actionFunc;
} EnOsk; // size = 0x264

extern const ActorInit En_Osk_InitVars;

#endif // Z_EN_OSK_H
