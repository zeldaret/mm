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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HAKUGIN_OBJ,
    sizeof(BgHakuginBombwall),
    (ActorFunc)BgHakuginBombwall_Init,
    (ActorFunc)BgHakuginBombwall_Destroy,
    (ActorFunc)BgHakuginBombwall_Update,
    (ActorFunc)BgHakuginBombwall_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABBFC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABC2E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABC58C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABC7FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCB5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCC00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCCE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCD98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/func_80ABCE60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Hakugin_Bombwall_0x80ABBFC0/BgHakuginBombwall_Draw.asm")
