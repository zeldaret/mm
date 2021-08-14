#ifndef Z_OBJ_BLOCKSTOP_H
#define Z_OBJ_BLOCKSTOP_H

#include "global.h"

struct ObjBlockstop;

typedef void (*ObjBlockstopActionFunc)(struct ObjBlockstop*, GlobalContext*);

typedef struct ObjBlockstop {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjBlockstopActionFunc actionFunc;
} ObjBlockstop; // size = 0x148

extern const ActorInit Obj_Blockstop_InitVars;

#endif // Z_OBJ_BLOCKSTOP_H
