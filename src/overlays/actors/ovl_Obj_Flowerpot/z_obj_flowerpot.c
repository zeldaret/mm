#include "z_obj_flowerpot.h"

#define FLAGS 0x00000000

#define THIS ((ObjFlowerpot*)thisx)

void ObjFlowerpot_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjFlowerpot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjFlowerpot_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjFlowerpot_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit Obj_Flowerpot_InitVars = {
    ACTOR_OBJ_FLOWERPOT,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FLOWERPOT,
    sizeof(ObjFlowerpot),
    (ActorFunc)ObjFlowerpot_Init,
    (ActorFunc)ObjFlowerpot_Destroy,
    (ActorFunc)ObjFlowerpot_Update,
    (ActorFunc)ObjFlowerpot_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_80A1D3A0[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x05CBFFBE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 100, 0 }, 12 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x0580C71C, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 300, 0 }, 12 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A1D3E8 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    2, D_80A1D3A0, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A1D414[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -20000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1600, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_80A1D3A0[2];
extern ColliderJntSphInit D_80A1D3E8;
extern InitChainEntry D_80A1D414[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B3D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BA04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BA44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BD80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C0FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CBF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CD10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CEF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Draw.asm")
