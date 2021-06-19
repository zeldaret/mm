#ifndef Z_OBJ_VISIBLOCK_H
#define Z_OBJ_VISIBLOCK_H

#include <global.h>

struct ObjVisiblock;

typedef struct ObjVisiblock {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ UNK_TYPE1 unk15C[0x4];
} ObjVisiblock; // size = 0x160

extern const ActorInit Obj_Visiblock_InitVars;

#endif // Z_OBJ_VISIBLOCK_H
