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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/EnHakurock_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/EnHakurock_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B21BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B21EA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B21FFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B22040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B220A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B221E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B222AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B2242C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B224C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B22500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B226AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B22750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/EnHakurock_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B228F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B229A4.asm")
