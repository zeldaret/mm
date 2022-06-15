#ifndef Z_DM_HINA_H
#define Z_DM_HINA_H

#include "global.h"

struct DmHina;

typedef void (*DmHinaActionFunc)(struct DmHina*, GlobalContext*);

typedef struct DmHina {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ DmHinaActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x10];
    /* 0x0158 */ f32 unk_158;
    /* 0x015C */ f32 unk_15C;
    /* 0x0160 */ char unk_160[0x24];
} DmHina; // size = 0x184

extern const ActorInit Dm_Hina_InitVars;

#endif // Z_DM_HINA_H
