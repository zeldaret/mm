#ifndef Z_OBJ_VISIBLOCK_H
#define Z_OBJ_VISIBLOCK_H

#include <global.h>

struct ObjVisiblock;

typedef struct ObjVisiblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} ObjVisiblock; // size = 0x160

extern const ActorInit Obj_Visiblock_InitVars;

#endif // Z_OBJ_VISIBLOCK_H
