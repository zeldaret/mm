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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HAKA_OBJ,
    sizeof(BgHakaTomb),
    (ActorFunc)BgHakaTomb_Init,
    (ActorFunc)BgHakaTomb_Destroy,
    (ActorFunc)BgHakaTomb_Update,
    (ActorFunc)BgHakaTomb_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/BgHakaTomb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/BgHakaTomb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/func_80BD6624.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/func_80BD6638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/func_80BD66AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/func_80BD6754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/func_80BD6768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/func_80BD67A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/func_80BD67BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/BgHakaTomb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Haka_Tomb_0x80BD6580/BgHakaTomb_Draw.asm")
