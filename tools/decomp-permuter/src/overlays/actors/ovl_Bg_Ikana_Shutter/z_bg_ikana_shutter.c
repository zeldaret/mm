#include "z_bg_ikana_shutter.h"

#define FLAGS 0x00000010

#define THIS ((BgIkanaShutter*)thisx)

void BgIkanaShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikana_Shutter_InitVars = {
    ACTOR_BG_IKANA_SHUTTER,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaShutter),
    (ActorFunc)BgIkanaShutter_Init,
    (ActorFunc)BgIkanaShutter_Destroy,
    (ActorFunc)BgIkanaShutter_Update,
    (ActorFunc)BgIkanaShutter_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5690.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/BgIkanaShutter_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/BgIkanaShutter_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5828.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5844.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5878.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5894.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD58F0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5910.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD599C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD59C4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD59F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5A18.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5AE8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5B04.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5B44.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5B60.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5BC4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5BD8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5C64.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/func_80BD5C8C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/BgIkanaShutter_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Shutter_0x80BD5690/BgIkanaShutter_Draw.asm")
