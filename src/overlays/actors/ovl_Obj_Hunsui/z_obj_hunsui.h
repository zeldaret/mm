#ifndef _Z_OBJ_HUNSUI_H_
#define _Z_OBJ_HUNSUI_H_

#include <global.h>

struct ObjHunsui;

typedef struct ObjHunsui {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x74];
} ObjHunsui; // size = 0x1B8

extern const ActorInit Obj_Hunsui_InitVars;

#endif
