#include "z_bg_ikana_rotaryroom.h"

#define FLAGS 0x00000030

#define THIS ((BgIkanaRotaryroom*)thisx)

void BgIkanaRotaryroom_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRotaryroom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRotaryroom_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRotaryroom_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikana_Rotaryroom_InitVars = {
    ACTOR_BG_IKANA_ROTARYROOM,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaRotaryroom),
    (ActorFunc)BgIkanaRotaryroom_Init,
    (ActorFunc)BgIkanaRotaryroom_Destroy,
    (ActorFunc)BgIkanaRotaryroom_Update,
    (ActorFunc)BgIkanaRotaryroom_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B802E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B80358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B80440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B80550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B80778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B80894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B80C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B80F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B814B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B816A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/BgIkanaRotaryroom_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/BgIkanaRotaryroom_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B818B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B818C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B8198C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B819DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B819F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81A80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81B84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/func_80B81DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/BgIkanaRotaryroom_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom/BgIkanaRotaryroom_Draw.s")
