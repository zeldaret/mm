#include "z_bg_ikana_block.h"

#define FLAGS 0x00000010

#define THIS ((BgIkanaBlock*)thisx)

void BgIkanaBlock_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBlock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBlock_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikana_Block_InitVars = {
    ACTOR_BG_IKANA_BLOCK,
    ACTORTYPE_BG,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(BgIkanaBlock),
    (ActorFunc)BgIkanaBlock_Init,
    (ActorFunc)BgIkanaBlock_Destroy,
    (ActorFunc)BgIkanaBlock_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EA60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EB30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EB64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EB7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EB94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7ECFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7ED54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EDC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EE70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7EEB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/BgIkanaBlock_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/BgIkanaBlock_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F00C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F034.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F0A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F0D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F1A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/BgIkanaBlock_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Block_0x80B7EA60/func_80B7F564.asm")
