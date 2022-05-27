/*
 * File: z_bg_sinkai_kabe.c
 * Overlay: ovl_Bg_Sinkai_Kabe
 * Description: Large Rotating Green Rupee
 */

#include "z_bg_sinkai_kabe.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgSinkaiKabe*)thisx)

void BgSinkaiKabe_Init(Actor* thisx, GlobalContext* globalCtx);
void BgSinkaiKabe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgSinkaiKabe_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_06000048;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe/BgSinkaiKabe_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe/BgSinkaiKabe_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe/func_80B6DA20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Sinkai_Kabe/BgSinkaiKabe_Update.s")
