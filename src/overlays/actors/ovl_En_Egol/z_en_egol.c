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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_EG,
    sizeof(EnEgol),
    (ActorFunc)EnEgol_Init,
    (ActorFunc)EnEgol_Destroy,
    (ActorFunc)EnEgol_Update,
    (ActorFunc)EnEgol_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7C990.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7CA18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7CBC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7CD08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/EnEgol_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/EnEgol_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D140.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D1E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D240.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D27C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D2C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D710.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7D780.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7DAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7DAF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E2E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E344.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E478.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E4B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E7EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E924.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7E9D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EA28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EA88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EAD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EB14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EB54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EB90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EBDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EC84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7ED14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7EFB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/EnEgol_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7F8E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A7FAFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/EnEgol_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A80508.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A80750.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Egol_0x80A7C990/func_80A80904.asm")
