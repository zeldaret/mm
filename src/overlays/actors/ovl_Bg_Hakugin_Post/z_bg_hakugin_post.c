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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9ACD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9ACF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AD18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AEB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AFB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B32C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B3BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B46C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9BC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9BD24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C228.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/BgHakuginPost_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/BgHakuginPost_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CA94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CAA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CD00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CD14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D0A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D0B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D1E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D2C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D3E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/BgHakuginPost_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D61C.asm")
