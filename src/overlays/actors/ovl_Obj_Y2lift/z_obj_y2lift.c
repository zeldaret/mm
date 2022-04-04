/*
 * File: z_obj_y2lift.c
 * Overlay: ovl_Obj_Y2lift
 * Description: Unused elevator platform
 */

#include "z_obj_y2lift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjY2lift*)thisx)

void ObjY2lift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Y2lift_InitVars = {
    ACTOR_OBJ_Y2LIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjY2lift),
    (ActorFunc)ObjY2lift_Init,
    (ActorFunc)ObjY2lift_Destroy,
    (ActorFunc)ObjY2lift_Update,
    (ActorFunc)ObjY2lift_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9A940[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80B9A940[];

extern UNK_TYPE D_06001680;
extern UNK_TYPE D_060019B0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2lift/ObjY2lift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2lift/ObjY2lift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2lift/ObjY2lift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2lift/ObjY2lift_Draw.s")
