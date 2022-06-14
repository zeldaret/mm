/*
 * File: z_bg_dkjail_ivy.c
 * Overlay: ovl_Bg_Dkjail_Ivy
 * Description: Cuttable Ivy wall (beneath Woodfall Temple, Swamp Spider House)
 */

#include "z_bg_dkjail_ivy.h"

#define FLAGS 0x00000000

#define THIS ((BgDkjailIvy*)thisx)

void BgDkjailIvy_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDkjailIvy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDkjailIvy_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDkjailIvy_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Dkjail_Ivy_InitVars = {
    ACTOR_BG_DKJAIL_IVY,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DKJAIL_OBJ,
    sizeof(BgDkjailIvy),
    (ActorFunc)BgDkjailIvy_Init,
    (ActorFunc)BgDkjailIvy_Destroy,
    (ActorFunc)BgDkjailIvy_Update,
    (ActorFunc)BgDkjailIvy_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ADE950 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01000200, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 20, 80, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ADE98C[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80ADE950;
extern InitChainEntry D_80ADE98C[];

extern UNK_TYPE D_06000080;
extern UNK_TYPE D_060011A8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE6AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE7E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Draw.s")
