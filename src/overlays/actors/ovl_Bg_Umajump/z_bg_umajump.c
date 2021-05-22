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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_80919F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_80919FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/BgUmajump_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/BgUmajump_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/BgUmajump_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A5A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A7B0.asm")
