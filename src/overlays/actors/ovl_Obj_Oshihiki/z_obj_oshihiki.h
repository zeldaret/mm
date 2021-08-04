#ifndef Z_OBJ_OSHIHIKI_H
#define Z_OBJ_OSHIHIKI_H

#include "global.h"

struct ObjOshihiki;

typedef void (*ObjOshihikiActionFunc)(struct ObjOshihiki* this, GlobalContext* globalCtx);

typedef struct ObjOshihiki {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjOshihikiActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x6C];
} ObjOshihiki; // size = 0x1CC

extern const ActorInit Obj_Oshihiki_InitVars;

#endif // Z_OBJ_OSHIHIKI_H
