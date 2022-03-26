#ifndef Z_OBJ_HARIKO_H
#define Z_OBJ_HARIKO_H

#include "global.h"

struct ObjHariko;

typedef void (*ObjHarikoActionFunc)(struct ObjHariko*, GlobalContext*);

typedef struct ObjHariko {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjHarikoActionFunc actionFunc;
    /* 0x0148 */ f32 unk148;
    /* 0x014C */ u16 unk14C;
    /* 0x014E */ u16 unk14E;
    /* 0x0150 */ u16 unk150;
    /* 0x0152 */ u16 unk152;
    /* 0x0152 */ u16 unk154;
} ObjHariko; // size = 0x158

extern const ActorInit Obj_Hariko_InitVars;

#endif // Z_OBJ_HARIKO_H
