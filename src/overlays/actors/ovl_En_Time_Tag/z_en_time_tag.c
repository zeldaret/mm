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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/EnTimeTag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/EnTimeTag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80AC9FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80AC9FE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA0A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA12C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA3C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA7C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/func_80ACA840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Time_Tag_0x80AC9EA0/EnTimeTag_Update.asm")
