#include "z_en_hakurock.h"

#define FLAGS 0x00000030

#define THIS ((EnHakurock*)thisx)

void EnHakurock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hakurock_InitVars = {
    ACTOR_EN_HAKUROCK,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(EnHakurock),
    (ActorFunc)EnHakurock_Init,
    (ActorFunc)EnHakurock_Destroy,
    (ActorFunc)EnHakurock_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/EnHakurock_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/EnHakurock_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B21BE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B21EA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B21FFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B22040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B220A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B221E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B222AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B2242C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B224C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B22500.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B226AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B22750.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/EnHakurock_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B228F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hakurock_0x80B21B00/func_80B229A4.asm")
