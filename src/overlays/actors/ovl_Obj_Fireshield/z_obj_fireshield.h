#ifndef Z_OBJ_FIRESHIELD_H
#define Z_OBJ_FIRESHIELD_H

#include "global.h"

struct ObjFireshield;

typedef void (*ObjFireshieldActionFunc)(struct ObjFireshield* this, GlobalContext* globalCtx);

typedef struct ObjFireshield {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ ObjFireshieldActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0x18];
} ObjFireshield; // size = 0x1AC

extern const ActorInit Obj_Fireshield_InitVars;

#endif // Z_OBJ_FIRESHIELD_H
