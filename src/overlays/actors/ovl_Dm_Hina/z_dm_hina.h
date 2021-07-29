#ifndef Z_DM_HINA_H
#define Z_DM_HINA_H

#include "global.h"

struct DmHina;

typedef void (*DmHinaActionFunc)(struct DmHina* this, GlobalContext* globalCtx);

typedef struct DmHina {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ DmHinaActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x3C];
} DmHina; // size = 0x184

extern const ActorInit Dm_Hina_InitVars;

#endif // Z_DM_HINA_H
