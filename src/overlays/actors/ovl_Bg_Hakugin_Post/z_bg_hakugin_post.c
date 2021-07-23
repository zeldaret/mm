#include "z_bg_hakugin_post.h"

#define FLAGS 0x00000030

#define THIS ((BgHakuginPost*)thisx)

void BgHakuginPost_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginPost_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginPost_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Hakugin_Post_InitVars = {
    ACTOR_BG_HAKUGIN_POST,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKUGIN_OBJ,
    sizeof(BgHakuginPost),
    (ActorFunc)BgHakuginPost_Init,
    (ActorFunc)BgHakuginPost_Destroy,
    (ActorFunc)BgHakuginPost_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A9D8B8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000100, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 276, 0, 20, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A9D8F8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80A9D8B8;
extern InitChainEntry D_80A9D8F8[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9ACD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9ACF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9AD18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9AE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9AEB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9AFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B32C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B3BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B46C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9B554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9BC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9BD24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9C058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9C18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9C228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9C634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9C854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/BgHakuginPost_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/BgHakuginPost_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CA94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CAA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CD00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CD14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9CE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D0A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D0B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D1E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D2C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D3E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/BgHakuginPost_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Post/func_80A9D61C.s")
