#ifndef Z_OBJ_AQUA_H
#define Z_OBJ_AQUA_H

#include "global.h"

#define AQUA_HOT(thisx) ((thisx)->params & 1)
#define OBJAQUA_1 1

struct ObjAqua;

typedef void (*ObjAquaActionFunc)(struct ObjAqua*, GlobalContext*);

typedef struct ObjAqua {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ ObjAquaActionFunc actionFunc;
    /* 0x0194 */ s16 counter;
    /* 0x0196 */ u8 alpha;
    /* 0x0198 */ s16 unk_198;
} ObjAqua; // size = 0x19C

extern const ActorInit Obj_Aqua_InitVars;

#endif // Z_OBJ_AQUA_H
