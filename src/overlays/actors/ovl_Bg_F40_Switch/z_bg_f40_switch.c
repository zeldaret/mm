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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/func_80BC47B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/BgF40Switch_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/BgF40Switch_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/func_80BC4B20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/func_80BC4B94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/func_80BC4BB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/func_80BC4C68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/func_80BC4D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/BgF40Switch_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Switch_0x80BC47B0/BgF40Switch_Draw.asm")
