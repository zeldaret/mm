#include "z_en_nwc.h"

#define FLAGS 0x00000010

#define THIS ((EnNwc*)thisx)

void EnNwc_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNwc_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNwc_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNwc_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Nwc_InitVars = {
    ACTOR_EN_NWC,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_NWC,
    sizeof(EnNwc),
    (ActorFunc)EnNwc_Init,
    (ActorFunc)EnNwc_Destroy,
    (ActorFunc)EnNwc_Update,
    (ActorFunc)EnNwc_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/EnNwc_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/EnNwc_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944320.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_809445D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944630.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_809447A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_809448A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_809449D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944A50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944E44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944EFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80944FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_8094506C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/EnNwc_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/EnNwc_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_8094529C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nwc_0x809441E0/func_80945310.asm")
