#ifndef Z_EFF_ZORABAND_H
#define Z_EFF_ZORABAND_H

#include "global.h"

struct EffZoraband;

typedef void (*EffZorabandActionFunc)(struct EffZoraband* this, GlobalContext* globalCtx);

typedef struct EffZoraband {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4];
    /* 0x0148 */ EffZorabandActionFunc actionFunc;
} EffZoraband; // size = 0x14C

extern const ActorInit Eff_Zoraband_InitVars;

#endif // Z_EFF_ZORABAND_H
