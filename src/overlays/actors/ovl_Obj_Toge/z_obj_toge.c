/*
 * File: z_obj_toge.c
 * Overlay: ovl_Obj_Toge
 * Description: Blade Trap
 */

#include "z_obj_toge.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjToge*)thisx)

void ObjToge_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjToge_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjToge_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjToge_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809A477C(ObjToge* this, GlobalContext* globalCtx);
void func_809A481C(ObjToge* this, GlobalContext* globalCtx);
void func_809A48AC(ObjToge* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Toge_InitVars = {
    ACTOR_OBJ_TOGE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TRAP,
    sizeof(ObjToge),
    (ActorFunc)ObjToge_Init,
    (ActorFunc)ObjToge_Destroy,
    (ActorFunc)ObjToge_Update,
    (ActorFunc)ObjToge_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809A4CB0 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 20, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809A4D14[] = {
    ICHAIN_F32_DIV1000(terminalVelocity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_809A4CB0;
extern InitChainEntry D_809A4D14[];

extern UNK_TYPE D_06001400;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A41C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A42A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A43A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A43EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A4744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A477C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A4804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A481C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A488C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A48AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Draw.s")
