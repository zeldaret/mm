#include "z_bg_sinkai_kabe.h"

#define FLAGS 0x00000010

#define THIS ((BgSinkaiKabe*)thisx)

void BgSinkaiKabe_Init(Actor* thisx, GlobalContext* globalCtx);
void BgSinkaiKabe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgSinkaiKabe_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Sinkai_Kabe_InitVars = {
    ACTOR_BG_SINKAI_KABE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_SINKAI_KABE,
    sizeof(BgSinkaiKabe),
    (ActorFunc)BgSinkaiKabe_Init,
    (ActorFunc)BgSinkaiKabe_Destroy,
    (ActorFunc)BgSinkaiKabe_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe_0x80B6D660/BgSinkaiKabe_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe_0x80B6D660/BgSinkaiKabe_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe_0x80B6D660/func_80B6DA20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe_0x80B6D660/BgSinkaiKabe_Update.asm")
