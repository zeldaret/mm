#ifndef _Z_OBJ_KIBAKO_H_
#define _Z_OBJ_KIBAKO_H_

#include <global.h>

struct ObjKibako;

typedef struct ObjKibako {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x58];
} ObjKibako; // size = 0x19C

extern const ActorInit Obj_Kibako_InitVars;

#endif
