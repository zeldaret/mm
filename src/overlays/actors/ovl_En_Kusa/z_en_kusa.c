#include "z_en_kusa.h"

#define FLAGS 0x00800010

#define THIS ((EnKusa*)thisx)

void EnKusa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kusa_InitVars = {
    ACTOR_EN_KUSA,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnKusa),
    (ActorFunc)EnKusa_Init,
    (ActorFunc)EnKusa_Destroy,
    (ActorFunc)EnKusa_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809349E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80934AB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80934F58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80934FFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809350C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809350F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_8093517C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809351A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809354F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809355A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_8093561C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/EnKusa_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/EnKusa_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809358C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809358D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80935988.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809359AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80935B94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80935BBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80935CE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80935D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80936120.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80936168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809361A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809361B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80936220.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80936290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809362D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/EnKusa_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_80936414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kusa_0x809349E0/func_809365CC.asm")
