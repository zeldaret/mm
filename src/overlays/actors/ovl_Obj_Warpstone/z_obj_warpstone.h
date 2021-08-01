#ifndef Z_OBJ_WARPSTONE_H
#define Z_OBJ_WARPSTONE_H

#include <global.h>

struct ObjWarpstone;

typedef s32 (*ObjWarpstoneActionFunc)(struct ObjWarpstone* this, GlobalContext* globalCtx);

typedef struct ObjWarpstone {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk144[0x18];
    /* 0x15C */ ColliderCylinder collider; 
    /* 0x1A8 */ u8 unk1A8;
    /* 0x1A8 */ u8 unk1A9;
    /* 0x1AA */ u8 unk1AA;
    /* 0x1AC */ ObjWarpstoneActionFunc actionFunc;
} ObjWarpstone; // size = 0x1B0

extern const ActorInit Obj_Warpstone_InitVars;

#define GET_OWL_ID(this) ((u16)(this->actor.params & 0xF))
#define IS_OWL_HIT(owlId) (((void)0,gSaveContext.owlsHit) & (u16)gBitFlags[owlId])

#endif // Z_OBJ_WARPSTONE_H
