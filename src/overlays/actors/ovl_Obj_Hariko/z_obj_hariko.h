#ifndef Z_OBJ_HARIKO_H
#define Z_OBJ_HARIKO_H

#include "global.h"

struct ObjHariko;

typedef void (*ObjHarikoActionFunc)(struct ObjHariko*, GlobalContext*);

typedef struct ObjHariko {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjHarikoActionFunc actionFunc;
    /* 0x0148 */ f32 bobbleStep;
    /* 0x014C */ Vec3s headRotation;
    /* 0x0152 */ s16 headOffset;
    /* 0x0154 */ s16 unk154; // Set but not used
} ObjHariko; // size = 0x158

extern const ActorInit Obj_Hariko_InitVars;

#endif // Z_OBJ_HARIKO_H
