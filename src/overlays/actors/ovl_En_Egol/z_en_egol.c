#include "z_en_egol.h"

#define FLAGS 0x80000035

#define THIS ((EnEgol*)thisx)

void EnEgol_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEgol_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEgol_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEgol_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Egol_InitVars = {
    ACTOR_EN_EGOL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_EG,
    sizeof(EnEgol),
    (ActorFunc)EnEgol_Init,
    (ActorFunc)EnEgol_Destroy,
    (ActorFunc)EnEgol_Update,
    (ActorFunc)EnEgol_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7C990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7CA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7CBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7CD08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D1E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D2C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7DAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7DAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E2E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E4B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E7EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E9D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EA28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EB54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7ED14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EFB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7F8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7FAFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A80508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A80750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A80904.s")
