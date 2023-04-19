#include "z_bg_keikoku_spr.h"
#include "objects/object_keikoku_obj/object_keikoku_obj.h"

#define FLAGS 0x00000000

#define THIS ((BgKeikokuSpr*)thisx)

void BgKeikokuSpr_Init(Actor* thisx, PlayState* play);
void BgKeikokuSpr_Destroy(Actor* thisx, PlayState* play);
void BgKeikokuSpr_Update(Actor* thisx, PlayState* play);
void BgKeikokuSpr_Draw(Actor* thisx, PlayState* play);

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
    (ActorFunc)BgKeikokuSpr_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Spr/BgKeikokuSpr_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Spr/BgKeikokuSpr_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Spr/BgKeikokuSpr_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Spr/BgKeikokuSpr_Draw.s")
