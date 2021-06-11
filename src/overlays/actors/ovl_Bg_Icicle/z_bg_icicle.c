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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_ICICLE,
    sizeof(BgIcicle),
    (ActorFunc)BgIcicle_Init,
    (ActorFunc)BgIcicle_Destroy,
    (ActorFunc)BgIcicle_Update,
    (ActorFunc)BgIcicle_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/BgIcicle_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/BgIcicle_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/func_809C9B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/func_809C9D7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/func_809C9D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/func_809C9DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/func_809C9F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/func_809CA06C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/func_809CA0BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/BgIcicle_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icicle/BgIcicle_Draw.s")
