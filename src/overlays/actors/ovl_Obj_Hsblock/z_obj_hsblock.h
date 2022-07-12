#ifndef Z_OBJ_HSBLOCK_H
#define Z_OBJ_HSBLOCK_H

#include "global.h"

struct ObjHsblock;

typedef void (*ObjHsblockActionFunc)(struct ObjHsblock*, PlayState*);

typedef struct ObjHsblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ ObjHsblockActionFunc actionFunc;
} ObjHsblock; // size = 0x160

extern const ActorInit Obj_Hsblock_InitVars;

#endif // Z_OBJ_HSBLOCK_H
