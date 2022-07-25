#ifndef Z_OBJ_SWPRIZE_H
#define Z_OBJ_SWPRIZE_H

#include "global.h"

struct ObjSwprize;

typedef void (*ObjSwprizeActionFunc)(struct ObjSwprize*, PlayState*);

typedef struct ObjSwprize {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjSwprizeActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x4];
} ObjSwprize; // size = 0x14C

extern const ActorInit Obj_Swprize_InitVars;

#endif // Z_OBJ_SWPRIZE_H
