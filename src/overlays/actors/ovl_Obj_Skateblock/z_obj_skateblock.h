#ifndef Z_OBJ_SKATEBLOCK_H
#define Z_OBJ_SKATEBLOCK_H

#include "global.h"

struct ObjSkateblock;

typedef void (*ObjSkateblockActionFunc)(struct ObjSkateblock*, GlobalContext*);

typedef struct ObjSkateblock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjSkateblockActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x64];
} ObjSkateblock; // size = 0x1C4

extern const ActorInit Obj_Skateblock_InitVars;

#endif // Z_OBJ_SKATEBLOCK_H
