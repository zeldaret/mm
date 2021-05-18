#include "z_bg_breakwall.h"

#define FLAGS 0x00000030

#define THIS ((BgBreakwall*)thisx)

void BgBreakwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgBreakwall_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Breakwall_InitVars = {
    ACTOR_BG_BREAKWALL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(BgBreakwall),
    (ActorFunc)BgBreakwall_Init,
    (ActorFunc)NULL,
    (ActorFunc)BgBreakwall_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B736C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B73C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B73FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B74A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B74D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B751C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/BgBreakwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B767C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B76CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B77D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B77E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B782C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B78A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B78DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/BgBreakwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7B54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Breakwall_0x808B7360/func_808B7FE4.asm")
