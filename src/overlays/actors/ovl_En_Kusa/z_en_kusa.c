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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809349E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934F58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80934FFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809350C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809350F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_8093517C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809351A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809354F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809355A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_8093561C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809358C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809358D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935988.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809359AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935B94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80935D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809361A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809361B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809362D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/EnKusa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_80936414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa_0x809349E0/func_809365CC.asm")
