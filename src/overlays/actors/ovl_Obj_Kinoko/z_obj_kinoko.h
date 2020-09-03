#ifndef _Z_OBJ_KINOKO_H_
#define _Z_OBJ_KINOKO_H_

#include <global.h>

struct ObjKinoko;

typedef struct ObjKinoko {
    /* 0x000 */ Actor actor;
} ObjKinoko; // size = 0x144

extern const ActorInit Obj_Kinoko_InitVars;

#endif
