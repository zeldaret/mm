#ifndef Z_OBJ_MAKEOSHIHIKI_H
#define Z_OBJ_MAKEOSHIHIKI_H

#include "global.h"

struct ObjMakeoshihiki;

#define OBJMAKEOSHIHIKI_GET_PATHLISTINDEX(this) (((this)->actor.params >> 7) & 0x7F)
#define OBJMAKEOSHIHIKI_GET_SWITCHFLAG_1(this) ((this)->actor.home.rot.z & 0x7F)
#define OBJMAKEOSHIHIKI_GET_SWITCHFLAG_2(this) ((this)->actor.params & 0x7F)

typedef struct ObjMakeoshihiki {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Vec3s* pathPoints;
    /* 0x148 */ s32 pathCount;
} ObjMakeoshihiki; // size = 0x14C

extern const ActorInit Obj_Makeoshihiki_InitVars;

#endif // Z_OBJ_MAKEOSHIHIKI_H
