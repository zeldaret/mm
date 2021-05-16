#include "z_bg_umajump.h"

#define FLAGS 0x00000000

#define THIS ((BgUmajump*)thisx)

void BgUmajump_Init(Actor* thisx, GlobalContext* globalCtx);
void BgUmajump_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgUmajump_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Umajump_InitVars = {
    ACTOR_BG_UMAJUMP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(BgUmajump),
    (ActorFunc)BgUmajump_Init,
    (ActorFunc)BgUmajump_Destroy,
    (ActorFunc)BgUmajump_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_80919F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_80919FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/BgUmajump_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/BgUmajump_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/BgUmajump_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A5A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A7B0.s")
