#include "z_bg_dkjail_ivy.h"

#define FLAGS 0x00000000

#define THIS ((BgDkjailIvy*)thisx)

void BgDkjailIvy_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDkjailIvy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDkjailIvy_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDkjailIvy_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Dkjail_Ivy_InitVars = {
    ACTOR_BG_DKJAIL_IVY,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_DKJAIL_OBJ,
    sizeof(BgDkjailIvy),
    (ActorFunc)BgDkjailIvy_Init,
    (ActorFunc)BgDkjailIvy_Destroy,
    (ActorFunc)BgDkjailIvy_Update,
    (ActorFunc)BgDkjailIvy_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/func_80ADE230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/BgDkjailIvy_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/BgDkjailIvy_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/func_80ADE6AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/func_80ADE6C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/func_80ADE734.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/func_80ADE748.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/func_80ADE7E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/func_80ADE7F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/BgDkjailIvy_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dkjail_Ivy_0x80ADE230/BgDkjailIvy_Draw.asm")
