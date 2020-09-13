#ifndef Z_OBJ_HSBLOCK_H
#define Z_OBJ_HSBLOCK_H

#include <global.h>

struct ObjHsblock;

typedef struct ObjHsblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} ObjHsblock; // size = 0x160

extern const ActorInit Obj_Hsblock_InitVars;

#endif // Z_OBJ_HSBLOCK_H
