#include "z_en_time_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnTimeTag*)thisx)

void EnTimeTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTimeTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTimeTag_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Time_Tag_InitVars = {
    ACTOR_EN_TIME_TAG,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTimeTag),
    (ActorFunc)EnTimeTag_Init,
    (ActorFunc)EnTimeTag_Destroy,
    (ActorFunc)EnTimeTag_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/EnTimeTag_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/EnTimeTag_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80AC9FD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80AC9FE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA0A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA12C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA184.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA208.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA348.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA3C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA418.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA5F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA714.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA724.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA7C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Time_Tag_0x80AC9EA0/EnTimeTag_Update.asm")
