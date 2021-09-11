#ifndef Z_OBJ_AQUA_H
#define Z_OBJ_AQUA_H

#include "global.h"

struct ObjAqua;

typedef void (*ObjAquaActionFunc)(struct ObjAqua*, GlobalContext*);

typedef struct ObjAqua {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ ObjAquaActionFunc actionFunc;
    /* 0x0194 */ s16 unk_194; //counter for how long the actor lives?
    /* 0x0196 */ u8 unk_196; // alpha?
    /* 0x0197 */ char unk_197;
    /* 0x0198 */ s16 unk_198; // some sort of angle?
} ObjAqua; // size = 0x19C

extern const ActorInit Obj_Aqua_InitVars;

#endif // Z_OBJ_AQUA_H
