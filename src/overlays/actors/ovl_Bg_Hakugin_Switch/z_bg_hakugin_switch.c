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
    ACTORTYPE_SWITCH,
    FLAGS,
    OBJECT_GORONSWITCH,
    sizeof(BgHakuginSwitch),
    (ActorFunc)BgHakuginSwitch_Init,
    (ActorFunc)BgHakuginSwitch_Destroy,
    (ActorFunc)BgHakuginSwitch_Update,
    (ActorFunc)BgHakuginSwitch_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15790.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B157C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15A4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15A68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15B1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15B74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15E0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15E78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15F3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B15F88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B1606C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B160DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16180.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B161A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B162AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B163C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16400.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B16520.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B165A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/func_80B165E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Switch_0x80B15790/BgHakuginSwitch_Draw.asm")
