#ifndef _Z_OBJ_OCARINALIFT_H_
#define _Z_OBJ_OCARINALIFT_H_

#include <global.h>

struct ObjOcarinalift;

typedef struct ObjOcarinalift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x34];
} ObjOcarinalift; // size = 0x178

extern const ActorInit Obj_Ocarinalift_InitVars;

#endif
