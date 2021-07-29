#ifndef Z_OBJ_LIGHTBLOCK_H
#define Z_OBJ_LIGHTBLOCK_H

#include "global.h"

struct ObjLightblock;

typedef void (*ObjLightblockActionFunc)(struct ObjLightblock* this, GlobalContext* globalCtx);

typedef struct ObjLightblock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ ObjLightblockActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} ObjLightblock; // size = 0x1B0

extern const ActorInit Obj_Lightblock_InitVars;

#endif // Z_OBJ_LIGHTBLOCK_H
