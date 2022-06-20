/*
 * File: z_en_lift_nuts.c
 * Overlay: ovl_En_Lift_Nuts
 * Description: Deku Scrub Playground - Employee
 */

#include "z_en_lift_nuts.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnLiftNuts*)thisx)

void EnLiftNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Lift_Nuts_InitVars = {
    ACTOR_EN_LIFT_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnLiftNuts),
    (ActorFunc)EnLiftNuts_Init,
    (ActorFunc)EnLiftNuts_Destroy,
    (ActorFunc)EnLiftNuts_Update,
    (ActorFunc)EnLiftNuts_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AEBF28 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 25, 75, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AEBF54 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80AEBF28;
extern CollisionCheckInfoInit2 D_80AEBF54;

extern UNK_TYPE D_060029E8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9A80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9AC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/EnLiftNuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/EnLiftNuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA0B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA7A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEABF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEACF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAF14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB828.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB8A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB9E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEBB30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/EnLiftNuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEBC18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEBC90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/EnLiftNuts_Draw.s")
