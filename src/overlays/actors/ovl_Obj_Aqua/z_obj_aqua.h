#ifndef Z_OBJ_AQUA_H
#define Z_OBJ_AQUA_H

#include "global.h"

struct ObjAqua;

typedef void (*ObjAquaActionFunc)(struct ObjAqua*, GlobalContext*);

typedef struct ObjAqua {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ ObjAquaActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0x2];
    /* 0x0196 */ u8 unk_196;
    /* 0x0197 */ char unk_197[0x5];
} ObjAqua; // size = 0x19C

extern const ActorInit Obj_Aqua_InitVars;

#endif // Z_OBJ_AQUA_H
