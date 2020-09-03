#ifndef Z_OBJ_AQUA_H
#define Z_OBJ_AQUA_H

#include <global.h>

struct ObjAqua;

typedef struct ObjAqua {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x58];
} ObjAqua; // size = 0x19C

extern const ActorInit Obj_Aqua_InitVars;

#endif // Z_OBJ_AQUA_H
