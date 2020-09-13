#include "z_bg_icicle.h"

#define FLAGS 0x00000000

#define THIS ((BgIcicle*)thisx)

void BgIcicle_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Icicle_InitVars = {
    ACTOR_BG_ICICLE,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_ICICLE,
    sizeof(BgIcicle),
    (ActorFunc)BgIcicle_Init,
    (ActorFunc)BgIcicle_Destroy,
    (ActorFunc)BgIcicle_Update,
    (ActorFunc)BgIcicle_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/func_809C9B9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/func_809C9D7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/func_809C9D8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/func_809C9DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/func_809C9F28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/func_809CA06C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/func_809CA0BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Draw.asm")
