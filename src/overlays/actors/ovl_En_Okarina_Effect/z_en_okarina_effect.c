#include "z_en_okarina_effect.h"

#define FLAGS 0x02000010

#define THIS ((EnOkarinaEffect*)thisx)

void EnOkarinaEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaEffect_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Okarina_Effect_InitVars = {
    ACTOR_EN_OKARINA_EFFECT,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOkarinaEffect),
    (ActorFunc)EnOkarinaEffect_Init,
    (ActorFunc)EnOkarinaEffect_Destroy,
    (ActorFunc)EnOkarinaEffect_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Okarina_Effect_0x8096B0A0/func_8096B0A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Okarina_Effect_0x8096B0A0/EnOkarinaEffect_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Okarina_Effect_0x8096B0A0/EnOkarinaEffect_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Okarina_Effect_0x8096B0A0/func_8096B104.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Okarina_Effect_0x8096B0A0/func_8096B174.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Okarina_Effect_0x8096B0A0/func_8096B1FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Okarina_Effect_0x8096B0A0/EnOkarinaEffect_Update.asm")
