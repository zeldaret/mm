#include "z_en_time_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnTimeTag*)thisx)

void EnTimeTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTimeTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTimeTag_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Time_Tag_InitVars = {
    ACTOR_EN_TIME_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTimeTag),
    (ActorFunc)EnTimeTag_Init,
    (ActorFunc)EnTimeTag_Destroy,
    (ActorFunc)EnTimeTag_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/EnTimeTag_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/EnTimeTag_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80AC9FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80AC9FE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA0A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA12C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA3C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA5F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA7C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/func_80ACA840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Time_Tag/EnTimeTag_Update.s")
