#include "z_obj_warpstone.h"

#define FLAGS 0x00000009

#define THIS ((ObjWarpstone*)thisx)

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B92C00(ObjWarpstone* this, GlobalContext* globalCtx);
void func_80B92CD0(ObjWarpstone* this, GlobalContext* globalCtx);
void func_80B92DC4(ObjWarpstone* this, GlobalContext* globalCtx);

void ObjWarpstone_SetupAction(ObjWarpstone* this, ObjWarpstoneActionFunc actionFunc);

#if 0
const ActorInit Obj_Warpstone_InitVars = {
    ACTOR_OBJ_WARPSTONE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_SEK,
    sizeof(ObjWarpstone),
    (ActorFunc)ObjWarpstone_Init,
    (ActorFunc)ObjWarpstone_Destroy,
    (ActorFunc)ObjWarpstone_Update,
    (ActorFunc)ObjWarpstone_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B93220 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00100000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9324C[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B93220;
extern InitChainEntry D_80B9324C[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92C00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Draw.s")
