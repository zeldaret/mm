#include "z_bg_hakugin_switch.h"

#define FLAGS 0x00000010

#define THIS ((BgHakuginSwitch*)thisx)

void BgHakuginSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Hakugin_Switch_InitVars = {
    ACTOR_BG_HAKUGIN_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_GORONSWITCH,
    sizeof(BgHakuginSwitch),
    (ActorFunc)BgHakuginSwitch_Init,
    (ActorFunc)BgHakuginSwitch_Destroy,
    (ActorFunc)BgHakuginSwitch_Update,
    (ActorFunc)BgHakuginSwitch_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B157C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/BgHakuginSwitch_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/BgHakuginSwitch_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15A4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15E78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15F3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B15F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B1606C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B160DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B16180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B161A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B16244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B162AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B163C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B16400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B16494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B16520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B165A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/func_80B165E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/BgHakuginSwitch_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch/BgHakuginSwitch_Draw.s")
