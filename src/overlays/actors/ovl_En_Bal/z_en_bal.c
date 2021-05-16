#include "z_en_bal.h"

#define FLAGS 0x00000019

#define THIS ((EnBal*)thisx)

void EnBal_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBal_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBal_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bal_InitVars = {
    ACTOR_EN_BAL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BAL,
    sizeof(EnBal),
    (ActorFunc)EnBal_Init,
    (ActorFunc)EnBal_Destroy,
    (ActorFunc)EnBal_Update,
    (ActorFunc)EnBal_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/EnBal_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/EnBal_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61A6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A61E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A621C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A622A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A623CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A624DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A629C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62AC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62B78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A62FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A63158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A634B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A634C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A635DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A635F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A636AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A637FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A63884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/EnBal_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A63A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/func_80A63B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bal/EnBal_Draw.s")
