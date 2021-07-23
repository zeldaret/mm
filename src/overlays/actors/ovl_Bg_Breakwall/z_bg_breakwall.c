#include "z_bg_breakwall.h"

#define FLAGS 0x00000030

#define THIS ((BgBreakwall*)thisx)

void BgBreakwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgBreakwall_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808B82E0[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};


extern InitChainEntry D_808B82E0[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B736C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B73C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B73FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B74A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B74D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B751C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/BgBreakwall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B767C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B76CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B77D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B77E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B782C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B78A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B78DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/BgBreakwall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7D34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Breakwall/func_808B7FE4.s")
