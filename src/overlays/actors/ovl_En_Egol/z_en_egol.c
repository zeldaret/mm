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
    (ActorFunc)EnEgol_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7C990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7CA18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7CBC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7CD08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/EnEgol_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/EnEgol_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D1E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D2C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7D780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7DAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7DAF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E2E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E4B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E7EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7E9D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EA28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EA88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EAD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EB14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EB54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EB90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EBDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7ED14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7EFB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/EnEgol_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7F8E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A7FAFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/EnEgol_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A80508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A80750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Egol_0x80A7C990/func_80A80904.asm")
