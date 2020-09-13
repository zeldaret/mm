#include "z_en_lift_nuts.h"

#define FLAGS 0x02000019

#define THIS ((EnLiftNuts*)thisx)

void EnLiftNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Lift_Nuts_InitVars = {
    ACTOR_EN_LIFT_NUTS,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnLiftNuts),
    (ActorFunc)EnLiftNuts_Init,
    (ActorFunc)EnLiftNuts_Destroy,
    (ActorFunc)EnLiftNuts_Update,
    (ActorFunc)EnLiftNuts_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9A20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9A80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9AC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9B4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9B8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9BCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9F28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9F70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AE9FC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA044.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA0B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA128.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA1A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA7A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEA910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEABF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAC64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEACF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAEAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAF14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAF8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEAFA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB114.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB1C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB280.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB294.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB3E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB428.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB584.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB684.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB828.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB8A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB934.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEB9E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEBB30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEBC18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/func_80AEBC90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Lift_Nuts_0x80AE9A20/EnLiftNuts_Draw.asm")
