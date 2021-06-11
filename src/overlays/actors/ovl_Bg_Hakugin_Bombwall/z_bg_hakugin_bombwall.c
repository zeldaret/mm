#include "z_bg_hakugin_bombwall.h"

#define FLAGS 0x00000000

#define THIS ((BgHakuginBombwall*)thisx)

void BgHakuginBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Hakugin_Bombwall_InitVars = {
    ACTOR_BG_HAKUGIN_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKUGIN_OBJ,
    sizeof(BgHakuginBombwall),
    (ActorFunc)BgHakuginBombwall_Init,
    (ActorFunc)BgHakuginBombwall_Destroy,
    (ActorFunc)BgHakuginBombwall_Update,
    (ActorFunc)BgHakuginBombwall_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABBFC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABC2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABC58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABC7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCB5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCCE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCD98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Draw.s")
