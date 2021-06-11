#include "z_bg_goron_oyu.h"

#define FLAGS 0x00000030

#define THIS ((BgGoronOyu*)thisx)

void BgGoronOyu_Init(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Update(Actor* thisx, GlobalContext* globalCtx);
void BgGoronOyu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Goron_Oyu_InitVars = {
    ACTOR_BG_GORON_OYU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OYU,
    sizeof(BgGoronOyu),
    (ActorFunc)BgGoronOyu_Init,
    (ActorFunc)BgGoronOyu_Destroy,
    (ActorFunc)BgGoronOyu_Update,
    (ActorFunc)BgGoronOyu_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B40080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B4009C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B400C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B40100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B40160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B401F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B40308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/func_80B40394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/BgGoronOyu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/BgGoronOyu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/BgGoronOyu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Goron_Oyu/BgGoronOyu_Draw.s")
