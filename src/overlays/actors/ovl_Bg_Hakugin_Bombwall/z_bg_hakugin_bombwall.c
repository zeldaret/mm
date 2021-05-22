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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABBFC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABC2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABC58C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABC7FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCB5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCC00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCCE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCD98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Draw.asm")
