#ifndef _Z_OBJ_VISIBLOCK_H_
#define _Z_OBJ_VISIBLOCK_H_

#include <global.h>

struct ObjVisiblock;

typedef struct ObjVisiblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} ObjVisiblock; // size = 0x160

extern const ActorInit Obj_Visiblock_InitVars;

#endif
