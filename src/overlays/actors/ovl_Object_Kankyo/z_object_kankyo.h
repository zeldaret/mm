#ifndef Z_OBJECT_KANKYO_H
#define Z_OBJECT_KANKYO_H

#include "global.h"

struct ObjectKankyo;

typedef void (*ObjectKankyoActionFunc)(struct ObjectKankyo*, GlobalContext*);

typedef struct ObjectKankyo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x100C];
    /* 0x1150 */ ObjectKankyoActionFunc actionFunc;
} ObjectKankyo; // size = 0x1154

extern const ActorInit Object_Kankyo_InitVars;

#endif // Z_OBJECT_KANKYO_H
