#ifndef _Z_OBJ_HANA_H_
#define _Z_OBJ_HANA_H_

#include <global.h>

struct ObjHana;

typedef struct ObjHana {
    /* 0x000 */ Actor actor;
} ObjHana; // size = 0x144

extern const ActorInit Obj_Hana_InitVars;

#endif
