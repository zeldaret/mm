#ifndef Z_OBJ_VISIBLOCK_H
#define Z_OBJ_VISIBLOCK_H

#include <global.h>

struct ObjVisiblock;

typedef struct ObjVisiblock {
    /* 0x000 */ DynaPolyActor dyna;
} ObjVisiblock; // size = 0x160

extern const ActorInit Obj_Visiblock_InitVars;

#endif // Z_OBJ_VISIBLOCK_H
