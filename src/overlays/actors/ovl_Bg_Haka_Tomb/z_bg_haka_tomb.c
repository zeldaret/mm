#include "z_bg_haka_tomb.h"

#define FLAGS 0x00000000

#define THIS ((BgHakaTomb*)thisx)

void BgHakaTomb_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakaTomb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakaTomb_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakaTomb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Haka_Tomb_InitVars = {
    ACTOR_BG_HAKA_TOMB,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKA_OBJ,
    sizeof(BgHakaTomb),
    (ActorFunc)BgHakaTomb_Init,
    (ActorFunc)BgHakaTomb_Destroy,
    (ActorFunc)BgHakaTomb_Update,
    (ActorFunc)BgHakaTomb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/BgHakaTomb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/BgHakaTomb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/func_80BD6624.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/func_80BD6638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/func_80BD66AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/func_80BD6754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/func_80BD6768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/func_80BD67A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/func_80BD67BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/BgHakaTomb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Tomb/BgHakaTomb_Draw.s")
