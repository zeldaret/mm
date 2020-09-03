#include "z_bg_inibs_movebg.h"

#define FLAGS 0x00000030

#define THIS ((BgInibsMovebg*)thisx)

void BgInibsMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgInibsMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgInibsMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Inibs_Movebg_InitVars = {
    ACTOR_BG_INIBS_MOVEBG,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_INIBS_OBJECT,
    sizeof(BgInibsMovebg),
    (ActorFunc)BgInibsMovebg_Init,
    (ActorFunc)BgInibsMovebg_Destroy,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)BgInibsMovebg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Inibs_Movebg_0x80B96410/BgInibsMovebg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Inibs_Movebg_0x80B96410/BgInibsMovebg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Inibs_Movebg_0x80B96410/BgInibsMovebg_Draw.asm")
