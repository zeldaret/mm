#ifndef Z_OBJ_AQUA_H
#define Z_OBJ_AQUA_H

#include "global.h"

struct ObjAqua;

typedef void (*ObjAquaActionFunc)(struct ObjAqua* this, GlobalContext* globalCtx);

typedef struct ObjAqua {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ ObjAquaActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0x8];
} ObjAqua; // size = 0x19C

extern const ActorInit Obj_Aqua_InitVars;

#endif // Z_OBJ_AQUA_H
