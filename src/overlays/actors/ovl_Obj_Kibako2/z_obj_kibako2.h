#ifndef Z_OBJ_KIBAKO2_H
#define Z_OBJ_KIBAKO2_H

#include <global.h>

struct ObjKibako2;

typedef struct ObjKibako2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} ObjKibako2; // size = 0x1B0

extern const ActorInit Obj_Kibako2_InitVars;

#endif // Z_OBJ_KIBAKO2_H
