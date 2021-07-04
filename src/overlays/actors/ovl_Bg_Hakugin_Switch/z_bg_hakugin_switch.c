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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B157C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15A4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15A68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15E78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15F3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B1606C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B160DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B161A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B162AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B163C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B165A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B165E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Draw.asm")
