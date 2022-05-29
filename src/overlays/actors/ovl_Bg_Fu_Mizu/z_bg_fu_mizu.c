/*
 * File: z_bg_fu_mizu.c
 * Overlay: ovl_Bg_Fu_Mizu
 * Description: Water in Honey and Darling's Second Day game
 */

#include "z_bg_fu_mizu.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgFuMizu*)thisx)

void BgFuMizu_Init(Actor* thisx, GlobalContext* globalCtx);
void BgFuMizu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgFuMizu_Update(Actor* thisx, GlobalContext* globalCtx);
void BgFuMizu_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Fu_Mizu_InitVars = {
    ACTOR_BG_FU_MIZU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FU_KAITEN,
    sizeof(BgFuMizu),
    (ActorFunc)BgFuMizu_Init,
    (ActorFunc)BgFuMizu_Destroy,
    (ActorFunc)BgFuMizu_Update,
    (ActorFunc)BgFuMizu_Draw,
};

#endif

extern UNK_TYPE D_060037D8;
extern UNK_TYPE D_060037F8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fu_Mizu/BgFuMizu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fu_Mizu/BgFuMizu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fu_Mizu/func_80ADABA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fu_Mizu/BgFuMizu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fu_Mizu/BgFuMizu_Draw.s")
