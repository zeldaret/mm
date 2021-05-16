#include "z_en_kusa.h"

#define FLAGS 0x00800010

#define THIS ((EnKusa*)thisx)

void EnKusa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kusa_InitVars = {
    ACTOR_EN_KUSA,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnKusa),
    (ActorFunc)EnKusa_Init,
    (ActorFunc)EnKusa_Destroy,
    (ActorFunc)EnKusa_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809349E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80934AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80934F58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80934FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809350C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809350F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_8093517C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809351A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809354F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809355A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_8093561C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/EnKusa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/EnKusa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809358C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809358D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809359AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935BBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809361A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809361B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809362D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/EnKusa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809365CC.s")
