#include "z_bg_ikana_block.h"

#define FLAGS 0x00000010

#define THIS ((BgIkanaBlock*)thisx)

void BgIkanaBlock_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBlock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBlock_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikana_Block_InitVars = {
    ACTOR_BG_IKANA_BLOCK,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(BgIkanaBlock),
    (ActorFunc)BgIkanaBlock_Init,
    (ActorFunc)BgIkanaBlock_Destroy,
    (ActorFunc)BgIkanaBlock_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7ECFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7ED54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EDC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EE70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/BgIkanaBlock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/BgIkanaBlock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F0D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F1A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/BgIkanaBlock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F564.s")
