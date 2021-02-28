#include "z_bg_keikoku_spr.h"

#define FLAGS 0x00000000

#define THIS ((BgKeikokuSpr*)thisx)

void BgKeikokuSpr_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSpr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSpr_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSpr_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Keikoku_Spr_InitVars = {
    ACTOR_BG_KEIKOKU_SPR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KEIKOKU_OBJ,
    sizeof(BgKeikokuSpr),
    (ActorFunc)BgKeikokuSpr_Init,
    (ActorFunc)BgKeikokuSpr_Destroy,
    (ActorFunc)BgKeikokuSpr_Update,
    (ActorFunc)BgKeikokuSpr_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Spr_0x808C3A50/BgKeikokuSpr_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Spr_0x808C3A50/BgKeikokuSpr_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Spr_0x808C3A50/BgKeikokuSpr_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Spr_0x808C3A50/BgKeikokuSpr_Draw.asm")
