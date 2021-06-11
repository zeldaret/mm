#include "z_en_hakurock.h"

#define FLAGS 0x00000030

#define THIS ((EnHakurock*)thisx)

void EnHakurock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hakurock_InitVars = {
    ACTOR_EN_HAKUROCK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(EnHakurock),
    (ActorFunc)EnHakurock_Init,
    (ActorFunc)EnHakurock_Destroy,
    (ActorFunc)EnHakurock_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/EnHakurock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/EnHakurock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B21BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B21EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B21FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B22040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B220A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B221E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B222AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B2242C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B224C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B22500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B226AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B22750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/EnHakurock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B228F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B229A4.s")
