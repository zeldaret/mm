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
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DKJAIL_OBJ,
    sizeof(BgDkjailIvy),
    (ActorFunc)BgDkjailIvy_Init,
    (ActorFunc)BgDkjailIvy_Destroy,
    (ActorFunc)BgDkjailIvy_Update,
    (ActorFunc)BgDkjailIvy_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE6AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE7E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/func_80ADE7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dkjail_Ivy/BgDkjailIvy_Draw.s")
