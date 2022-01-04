#ifndef Z_OBJ_FLOWERPOT_H
#define Z_OBJ_FLOWERPOT_H

#include "global.h"

struct ObjFlowerpot;

typedef void (*ObjFlowerpotActionFunc)(struct ObjFlowerpot*, GlobalContext*);

#define ENOBJFLOWERPOT_GET_3F(thisx) ((thisx)->params & 0x3F)
#define ENOBJFLOWERPOT_GET_7F00(thisx) (((thisx)->params >> 8) & 0x7F)

typedef struct ObjFlowerpot {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colliderElements[2];
    /* 0x01E4 */ ObjFlowerpotActionFunc actionFunc;
    /* 0x01E8 */ s16 unk_1E8;
    /* 0x01EA */ u8 unk_1EA;
    /* 0x01EB */ s8 unk_1EB;
    /* 0x01EC */ s8 unk_1EC;
} ObjFlowerpot; // size = 0x1F0

extern const ActorInit Obj_Flowerpot_InitVars;

#endif // Z_OBJ_FLOWERPOT_H
