#include "z_bg_f40_switch.h"

#define FLAGS 0x00000010

#define THIS ((BgF40Switch*)thisx)

void BgF40Switch_Init(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Update(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_F40_Switch_InitVars = {
    ACTOR_BG_F40_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_F40_SWITCH,
    sizeof(BgF40Switch),
    (ActorFunc)BgF40Switch_Init,
    (ActorFunc)BgF40Switch_Destroy,
    (ActorFunc)BgF40Switch_Update,
    (ActorFunc)BgF40Switch_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC47B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Draw.s")
