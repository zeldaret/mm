#include "z_en_lift_nuts.h"

#define FLAGS 0x02000019

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9A80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9AC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9F28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA0B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA7A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEABF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEACF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAF14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAF8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB1C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB3E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB8A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB934.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB9E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEBB30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEBC18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEBC90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Draw.asm")
