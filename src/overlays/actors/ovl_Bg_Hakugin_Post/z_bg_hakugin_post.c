#include "z_bg_hakugin_post.h"

#define FLAGS 0x00000030

#define THIS ((BgHakuginPost*)thisx)

void BgHakuginPost_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginPost_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginPost_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Hakugin_Post_InitVars = {
    ACTOR_BG_HAKUGIN_POST,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HAKUGIN_OBJ,
    sizeof(BgHakuginPost),
    (ActorFunc)BgHakuginPost_Init,
    (ActorFunc)BgHakuginPost_Destroy,
    (ActorFunc)BgHakuginPost_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9ACD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9ACF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AD18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AE3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AEB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9AFB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B160.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B2B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B32C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B3BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B46C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9B554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9BC0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9BD24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C058.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C18C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C228.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9C854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/BgHakuginPost_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/BgHakuginPost_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CA94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CAA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CC84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CCA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CD00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CD14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CE00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9CE1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D0A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D0B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D1E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D2C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D3E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D434.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/BgHakuginPost_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Post_0x80A9ACD0/func_80A9D61C.asm")
