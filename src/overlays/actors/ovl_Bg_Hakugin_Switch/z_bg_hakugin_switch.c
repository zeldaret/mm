#include "z_bg_hakugin_switch.h"

#define FLAGS 0x00000010

#define THIS ((BgHakuginSwitch*)thisx)

void BgHakuginSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B16860 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000400, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 60, 10, 180, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B16904[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 130, ICHAIN_STOP),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B16910[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 260, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 360, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80B16860;
extern InitChainEntry D_80B16904[];
extern InitChainEntry D_80B16910[];
#endif

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
