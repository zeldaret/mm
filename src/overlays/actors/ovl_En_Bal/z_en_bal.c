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
    (ActorFunc)EnBal_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61A6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61C9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61CE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A621C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A622A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A623CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A624DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A629C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62AC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62B78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62DCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A634B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A634C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A635DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A635F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A636AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A637FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63B94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Draw.asm")
