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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BAL,
    sizeof(EnBal),
    (ActorFunc)EnBal_Init,
    (ActorFunc)EnBal_Destroy,
    (ActorFunc)EnBal_Update,
    (ActorFunc)EnBal_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/EnBal_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/EnBal_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61A18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61A44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61A6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61ADC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61B5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61C9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61CE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61DF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A61E5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62128.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A621C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A622A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A623CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A624DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A629C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62AC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62B30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62B78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62DCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62ED0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A62FAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A63158.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A634B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A634C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A635DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A635F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A636AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A637FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A63884.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/EnBal_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A63A10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/func_80A63B94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bal_0x80A61810/EnBal_Draw.asm")
