#ifndef Z_OBJ_JGAME_LIGHT_H
#define Z_OBJ_JGAME_LIGHT_H

#include "global.h"

struct ObjJgameLight;

#define OBJJGAMELIGHT_GET_7F(thisx) ((thisx)->params & 0x7F)

typedef struct ObjJgameLight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x78];
} ObjJgameLight; // size = 0x1BC

extern const ActorInit Obj_Jgame_Light_InitVars;

#endif // Z_OBJ_JGAME_LIGHT_H
