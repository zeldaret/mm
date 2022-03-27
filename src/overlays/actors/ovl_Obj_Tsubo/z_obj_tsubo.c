/*
 * File: z_obj_tsubo.c
 * Overlay: ovl_Obj_Tsubo
 * Description: Pots
 */

#include "z_obj_tsubo.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_800000 | ACTOR_FLAG_4000000)

#define THIS ((ObjTsubo*)thisx)

void ObjTsubo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTsubo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTsubo_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80928928(ObjTsubo* this, GlobalContext* globalCtx);
void func_809289E4(ObjTsubo* this, GlobalContext* globalCtx);
void func_80928D80(ObjTsubo* this, GlobalContext* globalCtx);
void func_80928F18(ObjTsubo* this, GlobalContext* globalCtx);
void func_8092926C(ObjTsubo* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Tsubo_InitVars = {
    ACTOR_OBJ_TSUBO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjTsubo),
    (ActorFunc)ObjTsubo_Init,
    (ActorFunc)ObjTsubo_Destroy,
    (ActorFunc)ObjTsubo_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809295B0 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x05CBFFBE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 12, 30, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809295DC[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(terminalVelocity, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_809295B0;
extern InitChainEntry D_809295DC[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809275C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092762C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092776C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092788C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/ObjTsubo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/ObjTsubo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809282F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092860C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809289B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809289E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928D80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809291DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092926C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/ObjTsubo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809294B0.s")
