#ifndef Z_OBJ_WARPSTONE_H
#define Z_OBJ_WARPSTONE_H

#include <global.h>

struct ObjWarpstone;

typedef struct ObjWarpstone {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk144[0x18];
    /* 0x15C */ ColliderCylinder collider; 
    /* 0x1A8 */ char unk1A8[0x2];
    /* 0x1AA */ UNK_TYPE1 unk1AA;
    /* 0x1AC */ UNK_TYPE unk1AC;
} ObjWarpstone; // size = 0x1B0

extern const ActorInit Obj_Warpstone_InitVars;

#define GET_OWL_ID(this) ((u16)(this->actor.params & 0xF))
#define IS_OWL_HIT(owlId) (((void)0,gSaveContext.owlsHit) & (u16)gBitFlags[owlId])

#endif // Z_OBJ_WARPSTONE_H
