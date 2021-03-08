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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9D7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9D8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809C9F28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809CA06C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/func_809CA0BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Icicle_0x809C9A60/BgIcicle_Draw.asm")
