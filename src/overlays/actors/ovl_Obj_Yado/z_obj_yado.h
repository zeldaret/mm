#ifndef _Z_OBJ_YADO_H_
#define _Z_OBJ_YADO_H_

#include <global.h>

struct ObjYado;

typedef struct ObjYado {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ObjYado; // size = 0x148

extern const ActorInit Obj_Yado_InitVars;

#endif
