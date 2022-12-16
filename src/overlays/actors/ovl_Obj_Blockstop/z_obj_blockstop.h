#ifndef Z_OBJ_BLOCKSTOP_H
#define Z_OBJ_BLOCKSTOP_H

#include "global.h"

struct ObjBlockstop;

typedef void (*ObjBlockstopActionFunc)(struct ObjBlockstop*, PlayState*);

typedef struct ObjBlockstop {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjBlockstopActionFunc actionFunc;
} ObjBlockstop; // size = 0x148

#endif // Z_OBJ_BLOCKSTOP_H
