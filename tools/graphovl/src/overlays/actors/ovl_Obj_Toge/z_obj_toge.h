#ifndef Z_OBJ_TOGE_H
#define Z_OBJ_TOGE_H

#include "global.h"

struct ObjToge;

typedef void (*ObjTogeActionFunc)(struct ObjToge*, GlobalContext*);

typedef struct ObjToge {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ ObjTogeActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0x3C];
} ObjToge; // size = 0x1D0

extern const ActorInit Obj_Toge_InitVars;

#endif // Z_OBJ_TOGE_H
